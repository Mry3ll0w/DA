// ###### Config options ################


// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include <vector>

using namespace Asedio;
/*
selected id ==> contiene el id de la defensa que se ha seleccionado 
*/
//Estaria bien crear una estructura para el almacenado de las defensas para el tsp

//codigo para rellenar la TSP (defensa (valor de la funcion dada) e id de la defensa)

//hacer algoritmo de recuperacion y rellenar la lista de selected id de las defensas

//Consideracion ==> hay que comprar la primera de la lista de defensas 

//como comprobar y tal ../simulador -level -l 3324 -ases 1000 -v

//Formalice una funcion que asigne un valor a la funcion que asigna un determinado valor a cada uno
//de los tipos de defensas

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 1                                */
/* -------------------------------------------------------------------------- */
//para el almacenado de las defensas , usaremos un struct para hacer uso del metodo sort de list
struct defensa_valoracion{

    Defense * d;

    float valoracion;

    defensa_valoracion(Defense * d_, float v):d(d_),valoracion(v){}

    //ordenaremos segun el coste de la defensa (almacenado en defensa.cost) para una correcta ordenacion de los datos
    bool operator < (const defensa_valoracion& b){

        return d->cost < b.d->cost;

    }

};

//asigna el valor de cada una de las defensas
std::list<defensa_valoracion> defense_value(std::list<Defense*>&defenses){
    std::list<defensa_valoracion> def_value_list;

    //el criterio para seleccionar cual es mejor es la suma del daño + la salud + el alcance menos el coste
    for (auto i : defenses)
    {
        def_value_list.push_back(defensa_valoracion(i,(i->damage+i->health+i->range)-i->cost));
    }

    return def_value_list;
}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 2                                */
/* -------------------------------------------------------------------------- */

//2) Describa la estructura o estructuras usadas para representar la tabla de subproblemas resueltos.
//se necesitaria trabajar con iteradores que mueva a la vez la matriz y la lista de defensa valoracion

//Aun teniendo el coste ya almacenado en defensa usaremos esta struct para poder llamar al sort de lista
//permitiendo así una ordenacion más óptima (de orden logaritmica).
struct TSP{
    
    //La matriz almacenara la tabla de subproblemas resueltos
    std::vector<std::vector<int>> matriz_tsp;
    
    //Constructor de struct (asigna un tamaño maximo a las filas y columnas de la TSP)
    TSP(const int& max_ases, std::list<defensa_valoracion>& list_defensas_coste);
    
    //Contiene la lista de defensas junto con su valoracion para realizar el algortimo de la mochila
    std::list<defensa_valoracion> def_val_list;

};

TSP::TSP(const int& max_ases, std::list<defensa_valoracion>& list_defensas_coste):def_val_list(list_defensas_coste){
    //Realiza la reserva de espacios (en este caso es limitarlo para rellenar con valores predeterminados)
    
    matriz_tsp = std::vector<std::vector<int>>(list_defensas_coste.size()); //el n de filas viene dado por la capacidad de la mochila + 1 
    for (size_t i = 0; i < list_defensas_coste.size(); i++)
    {
        matriz_tsp[i] = std::vector<int>(max_ases+1); //El n de columnas viene dado por el numero de elementos que hay
    }

    //ordenamos la lista de defensas_coste para poder tratarla con mayor optimizacion
    def_val_list.sort();

    //Rellenamos la matriz TSP 

    //Para poder trabajar con la matriz con comodidad usaremos un vector de pairs donde el primero sera el coste y el segundo la valoracion
    std::vector<std::pair<int,int>> v_coste_valor;

    for (auto i: def_val_list)//Lo subimos sin comprobar ordenacion, ya que esta viene ordenada
    {
        v_coste_valor.push_back(std::make_pair(i.d->cost,i.valoracion));    
    }
    


    //1) Inicializamos la fila inicial de la matriz_tsp

    //comenzamos la insercion de la fila de 0 capacidad
    for(int j = 0; j < max_ases+1; ++j){
        
        if (j < def_val_list.begin()->d->cost) //Comprobamos que la primera defensa se pueda pagar con 0 ases
        {
            matriz_tsp[0][j]=0;
        }
        
        else{ //En caso de poder pagarla guardamos la valoracion de la misma
            matriz_tsp[0][j]=def_val_list.begin()->valoracion; // metemos el valor del elemento que cabe en 0 
        }
    }
    
    //2) Rellenamos el resto de filas
    
    //comenzaremos en el segundo elemento ya que el primero la matriz ya esta relleno
    for ( int i=1; i < def_val_list.size() ; i++ ){

        for ( int j=0; j<max_ases+1; j++){
          
            if (j <  v_coste_valor[i].first)
            {
                matriz_tsp[i][j]=matriz_tsp[i-1][j]; //si el coste es mayor que el nº de ases, metemos el anterior  
            }
            else{
                
                matriz_tsp[i][j]=std::max(matriz_tsp[i-1][j],matriz_tsp[i-1][j-v_coste_valor[i].first]+v_coste_valor[i].second);
            
            }

        }
    
    }


}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 3                                */
/* -------------------------------------------------------------------------- */

// Recibe la struct tsp (que tiene la lista de defensas a colocar etc) y el maximo numero de ases
//Se asume que la TSP ya se ha creado e inicializado con exito
 int max_beneficio(TSP& tsp,const int& max_ases ){
    
    return tsp.matriz_tsp[tsp.def_val_list.size()-1][max_ases];//devolvemos el ultimo elemento de la matriz que contiene el max valor

}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 4                                */
/* -------------------------------------------------------------------------- */


void DEF_LIB_EXPORTED selectDefenses(std::list<Defense*> defenses, unsigned int ases, 
std::list<int> &selectedIDs, float mapWidth, float mapHeight, std::list<Object*> obstacles) {
    //es necesario comprar la primera defensa siempre
    std::list<Defense*>::iterator it = defenses.begin() ;
    selectedIDs.push_back((*it)->id);
    ases -=(*it)->cost;
    it++; //metemos la primera defensa siempre
    
    //Asignamos ahora a cada defensa una valoracion
    std::list<defensa_valoracion> def_v;
    def_v = defense_value(defenses);
    
    //Creamos un objeto de la struct TSP para obtener el maximo beneficio y la matriz de subproblemas resueltos
    TSP str_tsp(ases,def_v);
    
    //Llamaremos ahora a la funcion que rellena la TSP y nos da el maximo beneficio
    int benef_max = max_beneficio(str_tsp,ases);
    
    std::cout<<std::endl;
    std::cout<<std::endl;
    
    std::cout<<benef_max<<std::endl;
    
    std::cout<<std::endl;
    std::cout<<std::endl;
    
    
    //algoritmo para la insercion y seleccion de las defensas a colocar
    unsigned int cost = 0;
    //std::list<Defense*>::iterator it = defenses.begin();
    while(it != defenses.end()) {
        if(cost + (*it)->cost <= ases) {
            selectedIDs.push_back((*it)->id);
            cost += (*it)->cost;
        }
        ++it;
    }
}
