// ###### Config options ################



// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include "cronometro.h"

using namespace Asedio;      
using namespace Asedio;

/* -------------------------------------------------------------------------- */
/*                        ALGORITMOS NECESARIOS (FORO)                        */
/* -------------------------------------------------------------------------- */
Vector3 cellCenterToPosition(int i, int j, float cellWidth, float cellHeight)
{
    return Vector3((j * cellWidth) + cellWidth * 0.5f, (i * cellHeight) + cellHeight * 0.5f, 0);
}

void positionToCell(const Vector3 pos, int &i_out, int &j_out, float cellWidth, float cellHeight)
{
    i_out = (int)(pos.y * 1.0f / cellHeight);
    j_out = (int)(pos.x * 1.0f / cellWidth);
}

/* ------------------------- COMIENZO DE LA PRACTICA ------------------------ */

float defaultCellValue(int row, int col, bool** freeCells, int nCellsWidth, int nCellsHeight
    , float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses) {
    	
    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;

    Vector3 cellPosition((col * cellWidth) + cellWidth * 0.5f, (row * cellHeight) + cellHeight * 0.5f, 0);
    	
    float val = 0;
    for (List<Object*>::iterator it=obstacles.begin(); it != obstacles.end(); ++it) {
	    val += _distance(cellPosition, (*it)->position);
    }

    return val;
}

float cellValueExtractionCenter(int row, int col, bool **freeCells, int nCellsWidth, int nCellsHeight, 
float mapWidth, float mapHeight, List<Object *> obstacles)
{
    
    float cellWidth = mapWidth / nCellsWidth; //anchura de la celula
    float cellHeight = mapHeight / nCellsHeight;//altura de la celula
    //Aplicamos el criterio ==> cuanto mas cerca de un obstaculo mejor 
    //Usamos el tipo vector 3 para una comparativa (si esta vacia o no de forma mas sencilla)
    Vector3 t_posicion = cellCenterToPosition(row,col,cellWidth,cellHeight);
    float value = 0;
    for(auto i: obstacles){
        value+=i->position.subtract(t_posicion).length();
        //value+=_distance(t_position,i.position); 
        //me da fallos a pesar de que esto representa lo mismo que arriba
    }
    
    //el que tenga menor valor tendra mas obstaculos cerca ==> mayor puntuacion
    //por tanto lo invierto para tener mayor puntuacion
    return 1/value; // implemente aqui la funci�n que asigna valores a las celdas
}


bool funcion_factibilidad(List<Defense *> defenses, const Defense &d, List<Object *> obstacles, float mapHeight,
              float cellWidth, float cellHeight, float mapWidth, int row, int col, bool **freeCells)
{

    //definicion de variables
    Vector3 p = cellCenterToPosition(row,col,cellWidth,cellHeight); //Creamos la posicion con los datos dados
    bool token = true;

    //Primeiro comprobamos que la celda no esta en ninguna posicion limite
    if(p.x + d.radio > mapWidth ||p.x - d.radio < 0 ||
        p.y + d.radio > mapHeight ||p.y - d.radio < 0)
    {
        return false; //si se cumple alguna condicion la defensa no cabe al alcanzar posiciones limite del mapa
    }    
        //Comprobaremos que no colisionan con las defensas/obstaculos que ya estan colocadas
        for(auto i : obstacles){
            //Colisionara en caso de que las distancias entre puntos centrales de los obstaculos
            //sea menor que los radios de la defensa a colocar y el obstaculo
            if(_distance(p,i->position) < (d.radio + i->radio ))
                token = false;
        }
        if(token){
            //Se comprobara de forma similar a los obstaculos con las defensas
            for (auto i: defenses){
                if(_distance(p,i->position) < (d.radio + i->radio ))
                    token = false;
            }
        }
        
        
    return token;      

}



struct celda_valoracion
{
    int row, col;
    float value;
    celda_valoracion(int r = 0, int c = 0, float v = 0) : row(r), col(c), value(v) {}
    
    //Overload ctor de copia
    celda_valoracion operator =(const celda_valoracion& c){
        this->row = c.row; this->col = c.col;
        return *this;
    }

    //Overload operator < (En caso de ordencacion por lista)
    bool operator <(const celda_valoracion& c){
        return value < c.value;
    }

};
/* -------------------------------------------------------------------------- */
/*                           ALGORTIMO DE ORDENACION                          */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                          ALGORITMOS DE ORDENACION                          */
/* -------------------------------------------------------------------------- */


/* ----------------------- QUICKSORT/ORDENACION RAPIDA ---------------------- */

/* -------------------------------------------------------------------------- */
/*                             DOCUMENTATION_BLOCK                            */
/* -------------------------------------------------------------------------- */
/*
Preconditions: 
    1)An initilized vector of t elements
    2)size_t low : By default 0 (the first position of the vector to be sorted)
    3)size_t high : Last position of the vector to be sorted (by default vector.size() - 1 )

Created by @Mry3ll0w, under © GPL2.0.
*/ 
template <class t>
t partition(std::vector<t>& array, int low, int high) {
    
  t pivot = array[high];
  
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;  
      std::swap(array[i], array[j]);
    }
  }
  
  std::swap(array[i + 1], array[high]);
  
  return (i + 1);
}

template <class t>
void quickSort(std::vector<t>& array, int low, int high) {
  if (low < high) {
      
    t pi = partition(array, low, high);

    quickSort(array, low, pi - 1);

    quickSort(array, pi + 1, high);
  }
}  


/* -------------------- MERGESORT / ORDENACION POR FUSION ------------------- */
/* -------------------------------------------------------------------------- */
/*                                DOCUMENTACION                               */
/* -------------------------------------------------------------------------- */
/*
Implementacion del algoritmo mergesort / ordenacion por fusion
recibira una std::vector<t> &arr, size_t l, size_t m, size_t r

Precondiciones==> Los elementos de la lista deben tener sobrecargado el operador <
Postcondiciones ==> Devuelve la lista de los elementos t ordenados

Tipo de Algoritmo: Divide y Vencerás(Equilibrado)

El parámetro i representa la posición a partir de la cual pretende ordenarse el vector v. 
De forma análoga, el parámetro j representa posición del vector v hasta donde pretende 
realizarse la ordenación. El parámetro k representa la posición intermedia que divide 
el vector original en los dos subvectores que van a ser fusionados.

Created by @Mry3ll0w, under © GPL2.0
*/
template <class t>
void merge(std::vector<t> &arr, size_t l, size_t m, size_t r)
{
    size_t n1 = m - l + 1;
    size_t n2 = r - m;
        
    std::vector<t>L(n1),R(n2);
   
    for (int i = 0; i < n1; i++){//copia la parte izquierda al centro
        L[i] = arr[l + i];
    }
        
    for (int j = 0; j < n2; j++){//copia la parte derecha al centro
         R[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
  
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
   
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

}
 
template <class t>
void mergeSort(std::vector<t> &arr,size_t l,size_t r){
    if(l>=r){
        return;
    }
    size_t m = (l+r-1)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}




/* -------------------------------------------------------------------------- */
/*                           COLOCACION DE DEFENSAS                           */
/* -------------------------------------------------------------------------- */

void DEF_LIB_EXPORTED placeDefenses3(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight
              , List<Object*> obstacles, List<Defense*> defenses) {

    

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight; 
    int maxAttemps = 1000;
    std::vector<celda_valoracion> celdas_valoradas;
    int i, j, k;
    float aux;
    celda_valoracion auxCell;
    cronometro c;
    long int r = 0;

    /* -------------------------------------------------------------------------- */
    /*                                  ALGORITMO                                 */
    /* -------------------------------------------------------------------------- */
    c.activar();
    do {	
    /* ------------------------ NO TOCAR A PARTIR DE AQUI ----------------------- */

   

    /* -------------------------------------------------------------------------- */
    /*                 ASINGACION DEL CENTRO DE EXTRACCION (DEF 0)                */
    /* -------------------------------------------------------------------------- */

    //1) Obtenemos que celdas estan libres tras la colocacion de los obstaculos
    for (int i = 0; i < nCellsHeight; i++){
        
        for (int j = 0; j < nCellsWidth; j++)
        {
            if (freeCells[i][j] != false){
                
                celdas_valoradas.push_back(celda_valoracion(i, j, cellValueExtractionCenter(i, j, freeCells, nCellsWidth, nCellsHeight, 
                mapWidth, mapHeight, obstacles)));

            }
                
                
        }

    }
    
    //Ordenacion de las celdas valoradas aplicando los constructores de vector y lista CAMBIAR PARA QUICK SORT Y MERGESORT 
    
    std::list<celda_valoracion>aux_lista(celdas_valoradas.begin(),celdas_valoradas.end());//Creo una lista con los elementos de celdas
    aux_lista.sort();//Ordeno los elementos O(n) = n · log n
    celdas_valoradas = std::vector<celda_valoracion>(aux_lista.begin(),aux_lista.end());//los copio a la lista


    bool placed = false;
    celda_valoracion solution;
    List<Defense *>::iterator currentDefense = defenses.begin();

    //Algoritmo devorador para centro de extraccion
    while (!placed && !celdas_valoradas.empty())
    {
        solution = celdas_valoradas.back();
        celdas_valoradas.pop_back();
        if (funcion_factibilidad(defenses, *(*currentDefense), obstacles, mapHeight,
                     cellWidth, cellHeight, mapWidth, solution.row, solution.col, freeCells))
        {
            placed = true;
            freeCells[solution.row][solution.col] = false;
            (*currentDefense)->position = cellCenterToPosition(solution.row, solution.col, cellWidth, cellHeight);
        }
        
    }
    //Copia de los candidatos

    std::vector<celda_valoracion> celdas_libres_aux;

    //Insertamos las celdas aun libres en el vector 
    for (i = 0; i < nCellsHeight; i++){
        
        for (j = 0; j < nCellsWidth; j++)
        {
            if (freeCells[i][j])
                celdas_libres_aux.push_back(celda_valoracion(i, j, defaultCellValue(i,j,freeCells,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses)));
        }
    }

    //Ordenamos los elementos de forma similar a lo hecho con anterioridad CAMBIAR PARA QUICK SORT Y MERGESORT
    std::list<celda_valoracion>aux_lista2(celdas_libres_aux.begin(),celdas_libres_aux.end());//Creo una lista con los elementos de celdas
    aux_lista2.sort();//Ordeno los elementos O(n) = n · log n
    celdas_libres_aux = std::vector<celda_valoracion>(aux_lista2.begin(),aux_lista2.end());//los copio a la lista

    //Copiamos el contenido a las celdas originales para la insercion en el mapa de las defensas
    celdas_valoradas = celdas_libres_aux;

    std::vector<celda_valoracion>::iterator it;
    
    currentDefense++;//pasamos al segundo elemento ya que el primero ya se ha colocado (centro de extraccion)

    while (currentDefense != defenses.end())
    {
        
        placed = false;
        it = celdas_libres_aux.end();
        while (!placed && !celdas_valoradas.empty())
        {
            
            solution = celdas_valoradas.back();
            celdas_valoradas.pop_back();
            if (funcion_factibilidad(defenses, *(*currentDefense), obstacles, mapHeight, cellWidth, cellHeight, mapWidth, solution.row, solution.col, freeCells))
            {
                placed = true;
                (*currentDefense)->position = cellCenterToPosition(solution.row, solution.col, cellWidth, cellHeight);
                
                    it--;
                
                celdas_libres_aux.erase(it);
            }
        }
        celdas_valoradas.clear();
        celdas_valoradas = celdas_libres_aux;
        currentDefense++;
    }


	/* ------------------------ NO TOCAR A PARTIR DE AQUI ----------------------- */
		++r;

    } while(c.tiempo() < 1.0);
    c.parar();
    std::cout << (nCellsWidth * nCellsHeight) << '\t' << c.tiempo() / r << '\t' << c.tiempo()*2 / r << '\t' << c.tiempo()*3 / r << '\t' << c.tiempo()*4 / r << std::endl;
}
