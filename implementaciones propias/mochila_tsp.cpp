#include <iostream> 
#include <vector>

/* -------------------------- CABECERAS DE FUNCION -------------------------- */

int alg_mochila(const std::vector<std::vector<int>> & TSP, const size_t& volumen_mochila, std::vector<std::pair<int,int>>elementos);

//Rellena la tabla de subproblemas resueltos con los datos dados
//elementos [volumen, valor]
std::vector<std::vector<int>> rellenar_tsp(std::vector<std::vector<int>> & TSP, 
const size_t& volumen_mochila, std::vector<std::pair<int,int>>elementos);

//Calcula beneficio de los elementos
const int calcula_beneficio(const std::vector<std::pair<int,int>>&elementos,const int& capacidad,int tope_elemento);

/* -------------------------------------------------------------------------- */
/*                             MAIN PARA TRABAJAR                             */
/* -------------------------------------------------------------------------- */

int main(){
    std::vector<std::vector<int>>TSP;
    std::vector<std::pair<int,int>>elementos={{1,2},{2,5},{4,6},{5,10},{7,13},{8,16}};
    TSP = rellenar_tsp(TSP,8,elementos);

    for ( int i=0; i< elementos.size(); i++ ){
        for ( int j=0; j<8+1; j++ ){
          std::cout<<TSP[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

return 0;
}

/* -------------------------------------------------------------------------- */
/*                              IMPLEMENTACIONES                              */
/* -------------------------------------------------------------------------- */
const int calcula_beneficio(const std::vector<std::pair<int,int>>&elementos,const int& capacidad,int tope_elemento){
    int beneficio = 0;
    int capacidad_restante = capacidad; //controlamos la capacidad restante que queda al ir insertando elementos
    //Recorremos los elementos hasta el actual o termine el vector de elementos
    for (size_t k = tope_elemento; k < 1 && capacidad_restante > 0; --k)
    {
        std::cout<<"entro calcula_benf con: "<<capacidad<<std::endl;
        /*
        beneficio += elementos[k].second;//añadimos el beneficio 
        capacidad_restante-=elementos[k].first;//actualizamos la capacidad
        */
        if(elementos[k].second > elementos[k-1].second){
            beneficio += elementos[k].second;
            capacidad_restante-=elementos[k].first;
        }
        else{
            beneficio += elementos[k-1].second;
            capacidad_restante-=elementos[k-1].first;
        }
    }
    return beneficio;
}


std::vector<std::vector<int>> rellenar_tsp(std::vector<std::vector<int>> & TSP, 
const size_t& volumen_mochila, std::vector<std::pair<int,int>>elementos){

//1)Realizar la reserva de espacios (en este caso es limitarlo para rellenar con valores predeterminados)
  
    TSP = std::vector<std::vector<int>>(elementos.size()); //el n de filas viene dado por la capacidad de la mochila + 1 
    for (size_t i = 0; i < elementos.size(); ++i)
    {
        TSP[i] = std::vector<int>(volumen_mochila+1); //El n de columnas viene dado por el numero de elementos que hay
    }


//2) Rellenamos la TSP conforme a los datos de entrada PREGUNTAR SALGUERO 
/*      ESTE ALGORITMO VIENE DADO EN LAS TRANSPARENCIAS
mochila : v × p × n × c → r
//desde j ← 0 hasta c (El numero columnas)
//    si j < p[1]
//        f [1, j] ← 0
//    si no
//        f [1, j] ← v[1]
desde i ← 2 hasta n
    desde j ← 0 hasta c 
        si j < p[i]
            f [i, j] ← f [i − 1, j]
        si no
            f [i, j] ← máx(f [i − 1, j],f [i − 1, j − p[i]] + v[i])

r ← f [n, c]
    return TSP;
*/
    //Usamos este for para meter el primer elemento de la matriz (0) donde el peso es minimo
    for(int j = 0; j < volumen_mochila+1; ++j){
        if (j < elementos[1].first)
        {
            TSP[0][j]=0;
        }
        else{
            TSP[0][j]=elementos[1].second; // metemos el valor del elemento que cabe en 0 
        }
    }

return TSP;
}

int alg_mochila(const std::vector<std::vector<int>> & TSP, 
const size_t& volumen_mochila, std::vector<std::pair<int,int>>elementos){
return 0;
}