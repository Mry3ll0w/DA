#include <iostream>
#include <vector>
#include "algoritmost2.hpp"
#include <bits/stdc++.h>

#define _inf INT_MIN

using namespace std;//Avoid using std:: ....


std::vector<std::vector<int>> ejercicio5(std::vector<std::vector<int>> m);

int main(){

    std::vector<std::vector<int>> m_ad={
        {1,1,0,0},
        {0,1,0,1},
        {1,0,1,0},
        {0,0,1,1}
    };

    
    cout << warshall(m_ad,m_ad[0].size()) << endl;
    std::cout<<"-----------------------------------------------------------"<<std::endl;
    cout<<ejercicio5(m_ad)<<std::endl;


return 0;
}

/*
Empleando el algoritmo de Floyd, diseñe un algoritmo que reciba la matriz de adyacencia de
un grafo y devuelva su matriz de accesibilidad.
Utilícelo para calcular la matriz de accesibilidad de:
*/

std::vector<std::vector<int>> ejercicio5(std::vector<std::vector<int>> m){

    //Queso viejo, no termino de entender 
    for(size_t i = 0; i < m[0].size(); i++){
        for(size_t j = 0; j < m[0].size(); j++){

            if(m[i][j] == 0){
                m[i][j]=_inf;
            }

        }
    }

    m = floyd(m,m[0].size());

    for(size_t i = 0; i < m[0].size(); i++){
        for(size_t j = 0; j < m[0].size(); j++){

            if(m[i][j] == _inf){ 
                m[i][j]=0;
            }
            else{
                m[i][j]=1;
            }

        }
    }
return m;
}
