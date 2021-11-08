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
    bool operator < (const defensa_valoracion& b){
        return valoracion < b.valoracion;
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
struct def_cost{
    Defense *d;
    int cost;
    def_cost(const Defense* d_):d(const_cast<Defense*>(d_)),cost(d->cost){}
    bool operator <(const def_cost& d){return cost < d.cost;}
};

struct TSP{
    
    std::vector<std::vector<int>> matriz_tsp;
    //filas = numero defensas 
    //col = maximo numero de ases
    TSP(const int& n_defensas, const int& max_ases, const std::list<def_cost>& valoraciones);

    
    std::list<def_cost> def_cost_list;

};

//constructor de clase
TSP::TSP(const int& n_defensas, const int& max_ases,const std::list<def_cost>& valoraciones)
:def_cost_list(const_cast<std::list<def_cost>&>(valoraciones)){
        matriz_tsp = std::vector<std::vector<int>>(n_defensas);
        //con esto reservaremos el espacio suficiente para una matriz [n_defensas] [max_ases]
        for(size_t i = 0 ; i<n_defensas ; ++i){
            matriz_tsp[i]= std::vector<int>(max_ases);
        }
}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 3                                */
/* -------------------------------------------------------------------------- */


void DEF_LIB_EXPORTED selectDefenses(std::list<Defense*> defenses, unsigned int ases, 
std::list<int> &selectedIDs, float mapWidth, float mapHeight, std::list<Object*> obstacles) {
    //es necesario comprar la primera defensa siempre
    std::list<Defense*>::iterator it = defenses.begin() ;
    selectedIDs.push_back((*it)->id);
    ases -=(*it)->cost;

    unsigned int cost = 0;
    std::list<Defense*>::iterator it = defenses.begin();
    while(it != defenses.end()) {
        if(cost + (*it)->cost <= ases) {
            selectedIDs.push_back((*it)->id);
            cost += (*it)->cost;
        }
        ++it;
    }
}
