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
   /* 
    TSP = new int*[elementos.size()];//filas vienen dadas por el numero de elementos
    for (size_t i = 0; i < elementos.size(); i++)
    {
        TSP[i]=new int [volumen_mochila+1];
    }
   */ 
    TSP = std::vector<std::vector<int>>(elementos.size()); //el n de filas viene dado por la capacidad de la mochila + 1 
    for (size_t i = 0; i < elementos.size(); ++i)
    {
        TSP[i] = std::vector<int>(volumen_mochila+1); //El n de columnas viene dado por el numero de elementos que hay
    }


//2) Rellenamos la TSP conforme a los datos de entrada
    for (size_t i = 0; i < elementos.size(); i++)
    {
        for (size_t j = 0; j < volumen_mochila + 1; j++)
        {
            //meteremos ahora los beneficios posibles
            
            if(j == 0){//si esta en la primera posicion simplemente comprobamos cuanto cabe de cada elemento
                TSP[i][j] = 0; //no cabe nada ya que es de 0 capacidad
            }
            else { // cuando la capacidad no sea 0

                int benef_a = calcula_beneficio(elementos,j,i);
                int benef_b = calcula_beneficio(elementos,j-1,i);
                TSP[i][j] = std::max(benef_a,benef_b); //la tsp deb
            }

        }
        
    }
    return TSP;
}

int alg_mochila(const std::vector<std::vector<int>> & TSP, 
const size_t& volumen_mochila, std::vector<std::pair<int,int>>elementos){
return 0;
}