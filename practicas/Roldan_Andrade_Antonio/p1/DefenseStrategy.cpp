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


void DEF_LIB_EXPORTED placeDefenses(bool **freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, 
float mapHeight, std::list<Object *> obstacles, std::list<Defense *> defenses)
{

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;

    int maxAttemps = 1000;
    std::vector<celda_valoracion> celdas_valoradas;
    int i, j, k;
    float aux;
    celda_valoracion auxCell;

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
    
    //Ordenacion de las celdas valoradas
    /*
    for (i = 0; i < celdas_valoradas.size(); i++){
        for (k = i + 1; k < celdas_valoradas.size(); k++)
        {
            if (celdas_valoradas[k].value < celdas_valoradas[i].value)
            {
                auxCell = celdas_valoradas[i];
                celdas_valoradas[i] = celdas_valoradas[k];
                celdas_valoradas[k] = auxCell;
            }
        }

    }
    */
    


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

    std::vector<celda_valoracion> AuxCells;

    for (i = 0; i < nCellsHeight; i++)
        for (j = 0; j < nCellsWidth; j++)
        {
            if (freeCells[i][j])
                AuxCells.push_back(celda_valoracion(i, j, defaultCellValue(i,j,freeCells,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses)));
        }

    k = 0;

    for (i = 0; i < AuxCells.size(); i++)
        for (k = i + 1; k < AuxCells.size(); k++)
        {
            if (AuxCells[k].value < AuxCells[i].value)
            {
                auxCell = AuxCells[i];
                AuxCells[i] = AuxCells[k];
                AuxCells[k] = auxCell;
            }
        }

    celdas_valoradas.clear();
    celdas_valoradas = AuxCells;

    std::vector<celda_valoracion>::iterator it;
    int iterations;
    currentDefense++;

    while (currentDefense != defenses.end())
    {
        iterations = 0;
        placed = false;
        it = AuxCells.end();
        while (!placed && !celdas_valoradas.empty())
        {
            iterations++;
            solution = celdas_valoradas.back();
            celdas_valoradas.pop_back();
            if (funcion_factibilidad(defenses, *(*currentDefense), obstacles, mapHeight, cellWidth, cellHeight, mapWidth, solution.row, solution.col, freeCells))
            {
                placed = true;
                (*currentDefense)->position = cellCenterToPosition(solution.row, solution.col, cellWidth, cellHeight);
                while (iterations > 0)
                {
                    it--;
                    iterations--;
                }
                AuxCells.erase(it);
            }
        }
        celdas_valoradas.clear();
        celdas_valoradas = AuxCells;
        currentDefense++;
    }
}



/* -------------------------------------------------------------------------- */
/*                             CODIGO PROFESORADO                             */
/* -------------------------------------------------------------------------- */

#ifdef PRINT_DEFENSE_STRATEGY

float **cellValues = new float *[nCellsHeight];
for (int i = 0; i < nCellsHeight; ++i)
{
    cellValues[i] = new float[nCellsWidth];
    for (int j = 0; j < nCellsWidth; ++j)
    {
        cellValues[i][j] = ((int)(cellValue(i, j))) % 256;
    }
}
dPrintMap("strategy.ppm", nCellsHeight, nCellsWidth, cellHeight, cellWidth, freeCells, cellValues, std::list<Defense *>(), true);

for (int i = 0; i < nCellsHeight; ++i)
    delete[] cellValues[i];
delete[] cellValues;
cellValues = NULL;

#endif
