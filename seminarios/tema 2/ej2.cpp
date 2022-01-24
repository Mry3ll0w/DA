#include <iostream>
#include <vector>
#include "algoritmost2.hpp"
using namespace std;//Avoid using std:: ....

std::vector<pair<int, int>> recupera_elementos (std::vector<std::vector<int>> TSP, std::vector<pair<int, int>>l,
        size_t filas, size_t cols
);

int main(){

    //Relleno los elementos de la TSP, ya que te lo dan 
    std::vector<std::vector<int>>TSP;
    std::vector<std::pair<int,int>>elementos={{1,2},{2,5},{4,6},{5,10},{7,13},{8,16}};
    TSP = rellenar_tsp(TSP,8,elementos);
    auto l = recupera_elementos(TSP,elementos,elementos.size(),8);

    for(auto i : l){

        cout << i.first << " " << i.second <<endl;

    }

return 0;
}

/*
Diseñe un algoritmo que reciba la tabla de subproblemas resueltos de valores correspondiente a un ejemplar del problema 
de la mochila discreta y devuelva, en un conjunto, una de las posibles composiciones óptimas de la carga
Ejemplo de uso de la cabecera
    ordered_defenses = recupera_defensas(str_tsp.matriz_tsp,def_v,def_v.size(),ases,defenses);
*/

std::vector<pair<int, int>> recupera_elementos (std::vector<std::vector<int>> TSP, std::vector<pair<int, int>>l,
        size_t filas, size_t cols
)
{
    //Los pairs se contruyen con {coste/volumen, valor/beneficio}
    size_t i = filas -2; size_t j = cols - l[0].first;
    std::vector<pair<int, int>> sol;

    size_t it = l.size();
    it--;
    while( i > 0 ){
        
        if ( TSP [i][j] != TSP[i-1][j]){
            j-= l[it].first;
            sol.emplace_back(l[it]);
        }
        i--;
        it--;

    }

    if(TSP[0][j] != 0){
        sol.emplace_back(l[it]);//Existe un elemento de coste/volumen 0, por tanto lo coje
    }

return sol;
}

