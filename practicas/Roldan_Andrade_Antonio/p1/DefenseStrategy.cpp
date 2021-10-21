// ###### Config options ################

//#define PRINT_DEFENSE_STRATEGY 1    // generate map images

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

#ifdef PRINT_DEFENSE_STRATEGY
#include "ppm.h"
#endif

#ifdef CUSTOM_RAND_GENERATOR
RAND_TYPE SimpleRandomGenerator::a;
#endif

using namespace Asedio;
// Devuelve la posición en el mapa del centro de la celda (i,j)
// i - fila
// j - columna
// cellWidth - ancho de las celdas
// cellHeight - alto de las celdas
Vector3 cellCenterToPosition(int i, int j, float cellWidth, float cellHeight){ 
    return Vector3((j * cellWidth) + cellWidth * 0.5f, (i * cellHeight) + cellHeight * 0.5f, 0); 
}

// Devuelve la celda a la que corresponde una posición en el mapa
// pos - posición que se quiere convertir
// i_out - fila a la que corresponde la posición pos (resultado)
// j_out - columna a la que corresponde la posición pos (resultado)
// cellWidth - ancho de las celdas
// cellHeight - alto de las celdas
void positionToCell(const Vector3 pos, int &i_out, int &j_out, float cellWidth, float cellHeight){ 
    i_out = (int)(pos.y * 1.0f/cellHeight); j_out = (int)(pos.x * 1.0f/cellWidth); 
}


float cellValue(int row, int col, bool** freeCells, int nCellsWidth, int nCellsHeight
	, float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses) {
	//De forma similar al ejercicio inferior
    float cellWidth = mapWidth / nCellsWidth; //anchura de la celula
    float cellHeight = mapHeight / nCellsHeight;//altura de la celula
    /*Aplicamos el criterio ==> cuanto mas cerca de un obstaculo mejor 
    */
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

/*
FUNCION DE FACTIBILIDAD
 Diseñe una funcion de factibilidad explicita y descrıbala a continuacion.
 Entiendo que la funcion sirve para comprobar si es posible que se coloque algo en una celda
 (una defensa en x lugar)
 Parametros: 
    Row-> entero que representa una fila en la matriz del mapa
    col-> entero que representa una col en la matriz del mapa
    obstacles-> Recibe la lista de defensas colocadas en el mapa para iterar y comprobar que no coincidan
    Defenses-> Recibe la lista de obstacles en el mapa para iterar y comprobar que no coincidan
    freeCells -> Matriz con el numero de celdas libres
    mapHeight -> altura del mapa (eje z)
    mapWidth -> anchura del mapa (eje x)
    int nCellsWidth-> numero de celdas en total del eje x
    int nCellsHeight-> numero de celdas en total del eje z
    Defense d ==> Recibe una referencia a la defensa a colocar en la celda
    PREGUNTAR QUE SIGNIFICA QUE SEA UNA FUNCION DE FACTIBILIDAD EXPLICITA
*/
bool funcion_factibilidad(int row, int col, List<Object*> obstacles, List<Defense*> defenses,
bool **freeCells,float mapHeight, float mapWidth,int nCellsWidth, int nCellsHeight, const Defense& d){
    //definicion de variables
    float cellWidth = mapWidth / nCellsWidth; //anchura de la celula
    float cellHeight = mapHeight / nCellsHeight;//altura de la celula
    Vector3 p = cellCenterToPosition(row,col,cellWidth,cellHeight); //Creamos la posicion con los datos dados
    bool token = true;

    //Primeiro comprobamos que la celda no esta en ninguna posicion limite
    if(p.x + d.radio > mapWidth ||p.x - d.radio < 0 ||
        p.y + d.radio > mapHeight ||p.y - d.radio < 0)
    {
        return false; //si se cumple alguna condicion la defensa no cabe al alcanzar posiciones limite del mapa
    }    
    else{//Si no cumple el primer requisito no sera necesario continuar, en cambio , si lo cumple entonces:
        //Comprobaremos que no colisionan con las defensas/obstaculos que ya estan colocadas
        for(auto i : obstacles){
            //Colisionara en caso de que las distancias entre puntos centrales de los obstaculos
            //sea menor que los radios de la defensa a colocar y el obstaculo
            if((d.radio + i->radio)>_distance(p,i->position))
                token = false;
        }
        if(token){//si ya se ha detectado que no es posible colocarla en un obstaculo
                  //para que comprobar las defensas
            //Se comprobara de forma similar a los obstaculos con las defensas
            for (auto i: defenses){
                if((d.radio + i->radio)>_distance(p,i->position))
                    token = false;
            }
        }
    }
    return token;      
}


void DEF_LIB_EXPORTED placeDefenses(bool** freeCells, int nCellsWidth, int nCellsHeight, 
float mapWidth, float mapHeight, std::list<Object*> obstacles, std::list<Defense*> defenses) {

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight; 

    int maxAttemps = 1000;
    List<Defense*>::iterator currentDefense = defenses.begin();
    while(currentDefense != defenses.end() && maxAttemps > 0) {

        (*currentDefense)->position.x = ((int)(_RAND2(nCellsWidth))) * cellWidth + cellWidth * 0.5f;
        (*currentDefense)->position.y = ((int)(_RAND2(nCellsHeight))) * cellHeight + cellHeight * 0.5f;
        (*currentDefense)->position.z = 0; 
        ++currentDefense;
    }

#ifdef PRINT_DEFENSE_STRATEGY

    float** cellValues = new float* [nCellsHeight]; 
    for(int i = 0; i < nCellsHeight; ++i) {
       cellValues[i] = new float[nCellsWidth];
       for(int j = 0; j < nCellsWidth; ++j) {
           cellValues[i][j] = ((int)(cellValue(i, j))) % 256;
       }
    }
    dPrintMap("strategy.ppm", nCellsHeight, nCellsWidth, cellHeight, cellWidth, freeCells
                         , cellValues, std::list<Defense*>(), true);

    for(int i = 0; i < nCellsHeight ; ++i)
        delete [] cellValues[i];
	delete [] cellValues;
	cellValues = NULL;

#endif
}