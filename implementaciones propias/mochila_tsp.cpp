#include <iostream> 
#include <vector>

/* -------------------------- CABECERAS DE FUNCION -------------------------- */

int alg_mochila(const std::vector<std::vector<int>> & TSP, const size_t& volumen_mochila, std::vector<std::pair<int,int>>elementos);

//Rellena la tabla de subproblemas resueltos con los datos dados
//elementos [volumen, valor]
std::vector<std::vector<int>> rellenar_tsp(std::vector<std::vector<int>> & TSP, 
const size_t& volumen_mochila, std::vector<std::pair<int,int>>elementos);

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

int alg_mochila(const std::vector<std::vector<int>> & TSP, 
const size_t& volumen_mochila, std::vector<std::pair<int,int>>elementos){
return 0;
}