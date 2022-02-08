#include <vector>
#include <iostream>
#include <algorithm>

//Sobrecarga
template <class t>
std::ostream& operator<<(std::ostream&os, std::vector<std::vector<t>>m){
    for(int i = 0; i < m[0].size() ; ++i){
        for(int j = 0; j < m.size();++j){
            os << m[i][j] <<"  ";
        }
        os<<std::endl;
    }
    return os;
}

//Rellenar la TSP
std::vector<std::vector<int>> rellenar_tsp(std::vector<std::vector<int>> & TSP, 
const size_t& volumen_mochila, std::vector<std::pair<int,int>>elementos){

//1)Realizar la reserva de espacios (en este caso es limitarlo para rellenar con valores predeterminados)
  
    TSP = std::vector<std::vector<int>>(elementos.size()); //el n de filas viene dado por la capacidad de la mochila + 1 
    for (size_t i = 0; i < elementos.size(); ++i)
    {
        TSP[i] = std::vector<int>(volumen_mochila+1); //El n de columnas viene dado por el numero de elementos que hay
    }


//2) Rellenamos la TSP conforme a los datos de entrada (dados por elementos)

    //Usamos este for para meter el primer elemento de la matriz (0) donde el peso es minimo
    for(int j = 0; j < volumen_mochila+1; ++j){
        
        if (j < elementos[0].first)
        {
            TSP[0][j]=0;
        }
        
        else{
            TSP[0][j]=elementos[0].second; // metemos el valor del elemento que cabe en 0 
        }
    }

    for ( int i=1; i<elementos.size() ;i++ ){
        
        for ( int j=0; j< volumen_mochila+1 ; ++j){
        
            if (j < elementos[i].second)
            {
                TSP[i][j]= TSP[i-1][j];
            }
            
            else{
                
                TSP[i][j] = std::max(TSP[i-1][j], TSP[i-1][j-elementos[i].second]+elementos[i].first);
                
            }
            
        }
    }

return TSP;
}


//Algoritmo de Floyd ==> Obtencion de caminos minimos

std::vector<std::vector<int>> floyd (std::vector<std::vector<int>>g, int n_vertices){

    auto sol = g;

    for(size_t i = 0; i < n_vertices; i++){
        sol[i][i]=0;
    }

    for(size_t k = 0; k < n_vertices; k++){
        
        for(size_t i = 0; i < n_vertices; i++){
            
            for(size_t j = 0; j < n_vertices; j++){

                sol[i][j]= std::min(sol[i][j],sol[i][k]+sol[k][j]);
            
            }
        
        }
    
    }

return sol;
}


/* -------------------------------------------------------------------------- */
/*                            ALGORITMO DE WARSHALL                           */
/* -------------------------------------------------------------------------- */

//Recibe una matriz de adyancencia y crea su Clausura Reflexiva y transitiva, nos sirve para obtener desde una matriz de 
//adyacencia, una matriz de accesibilidad

std::vector<std::vector<int>> warshall(std::vector<std::vector<int>>m, int n_vertices){

    for(size_t i = 0; i < n_vertices;++i){
        m[i][i]= 1;
    }

    for(size_t k = 0; k < n_vertices; k++){
        
        for(size_t i = 0; i < n_vertices; i++){
    
            for (size_t j = 0; j < n_vertices; j++)
            {
                m[i][j] = (m[i][j] ||( m[i][k] && m[k][j]));
            }
        
        }
    }
return m;
} 