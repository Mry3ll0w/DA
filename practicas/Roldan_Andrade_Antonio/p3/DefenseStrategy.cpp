// ###### Config options ################



// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include "cronometro.h"

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
    float mapHeight, float mapWidth,int nCellsWidth, int nCellsHeight, Defense* d){
    //definicion de variables
    float cellWidth = mapWidth / nCellsWidth; //anchura de la celula
    float cellHeight = mapHeight / nCellsHeight;//altura de la celula
    Vector3 p = cellCenterToPosition(row,col,cellWidth,cellHeight); //Creamos la posicion con los datos dados
    bool token = true;

    //Primero comprobamos que la celda no esta en ninguna posicion limite
    if(p.x + d->radio > mapWidth ||  //Se sale por la derecha
        p.x - d->radio < 0 ||         //Se sale por la izquierda
        p.y + d->radio > mapHeight || //Se sale por abajo
        p.y - d->radio < 0)           //Se sale por arriba
    {
        token = false; //si se cumple alguna condicion la defensa no cabe al alcanzar posiciones limite del mapa
    }    
        //Comprobaremos que no colisionan con las defensas/obstaculos que ya estan colocadas
        for(auto i : obstacles){
            //Colisionara en caso de que las distancias entre puntos centrales de los obstaculos
            //sea menor que los radios de la defensa a colocar y el obstaculo
            if(_distance(p,i->position) < (d->radio + i->radio ))
                token = false;
        }
        if(token){
            //Se comprobara de forma similar a los obstaculos con las defensas
            for (auto i: defenses){
                if(_distance(p,i->position) < (d->radio + i->radio ))
                    token = false;
            }
        }
        
        
    return token;      
}//Necesito saltar a otra celda

//NECESITO ORDENAR Y COLOCAR CELDAS
//EN CASO DE NO ENCONTRAR CELDA FACTIBLE SE PASA A LA SIGUIENTE CELDA
//SI ES FACTIBLE ==> SE COLOCA Y SE ELIMINA CELDA DE LA LISTA
//COMPROBAR PARA TODAS LAS DEFENSAS Y YA




/* -------------------------------------------------------------------------- */
/*                          IMPLEMENTACIONES PROPIAS                          */
/* -------------------------------------------------------------------------- */
//int nCellsWidth X int nCellsHeight Y
//FREECELLS SE ITERA CON int [nCellsWidth] [nCellsHeight]

struct celda_valoracion{
    
    float valoracion;
    
    int pos_x;
    
    int pos_y;
    
    celda_valoracion(int a, int b, float v):pos_x(a), pos_y(b), valoracion(v) {}

    //Para hacer el sort llamando a lista que es de O(n)= n* log n
    bool operator < (const celda_valoracion & c){
        return valoracion < c.valoracion;
    }
    
    //para hacer la comparacion
    bool operator == (const celda_valoracion & c){
        return (pos_x == c.pos_x && pos_y == c.pos_y);
    }
    
};


/*
    1   2   3 
    4   5   6
    7   8   9

*/
std::list<celda_valoracion> valora_celdas(bool** freeCells, int nCellsWidth, int nCellsHeight
    , float mapWidth, float mapHeight, List<Object*> obstacles, List<Defense*> defenses){
    std::list<celda_valoracion> S;

    //Recorremos todas las posibles celdas del mapa para darle valoracion a cada una de ellas
    for ( int i=0; i<nCellsHeight ;i++ ){
        for ( int j=0; j<nCellsHeight; j++){
            
            if (freeCells[i][j])//Si esta libre -> valora la celda, si no para que 
            {
                float val = defaultCellValue(i,j,freeCells,nCellsWidth,nCellsHeight,mapWidth,mapHeight,obstacles,defenses);
                S.push_back(celda_valoracion(i,j,val));
            }
            
        }
    }
    //Ordenamos la lista S 
    S.sort();

    return S;

}

/* --------------------- Funcion para el max maxAttemps --------------------- */
int count_free_cells(bool** freeCells, int nCellsWidth, int nCellsHeight){
    size_t cont=0;
    for ( int i=0; i< nCellsHeight; i++ ){
        for ( int j=0; j< nCellsWidth; j++){
          if (!freeCells[i][j])
            ++cont;
          
        }
    }
return cont;
}



void DEF_LIB_EXPORTED placeDefenses3(bool** freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight
              , List<Object*> obstacles, List<Defense*> defenses) {

    

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight; 
    /* -------------------------------------------------------------------------- */
    /*                                   SANDBOX                                  */
    /* -------------------------------------------------------------------------- */
    //std::list<celda_valoracion>celdas_valoradas = valora_celdas(freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight,obstacles,defenses); 
    
    /* --------------------------- Variables Algortimo Principal -------------------------- */

    std::list<celda_valoracion>celdas_valoradas = valora_celdas(freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight,obstacles,defenses); 
    std::list<celda_valoracion>::iterator it_celdas_valoradas = celdas_valoradas.begin();
    bool erase_pos=false;
    bool placed = false;
    int maxAttemps = 1000;
	cronometro c;
    long int r = 0;

    /* -------------------------------------------------------------------------- */
    /*                                  ALGORITMO                                 */
    /* -------------------------------------------------------------------------- */
    c.activar();
    do {	
    /* ------------------------ NO TOCAR A PARTIR DE AQUI ----------------------- */
		
    
    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;

    int maxAttemps = 1000;
    std::vector<Cell> Cells;//cell es celda_valoracion
    int i, j, k;
    float aux;
    Cell auxCell;

    //Algoritmo centro extr
    for (i = 0; i < nCellsHeight; i++)
        for (j = 0; j < nCellsWidth; j++)
        {
            if (freeCells[i][j])
                Cells.push_back(Cell(i, j, cellValueExtr(i, j, freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles)));
        }

    for (i = 0; i < Cells.size(); i++)
        for (k = i + 1; k < Cells.size(); k++)
        {
            if (Cells[k].value < Cells[i].value)
            {
                auxCell = Cells[i];
                Cells[i] = Cells[k];
                Cells[k] = auxCell;
            }
        }

    bool placed = false;
    Cell solution;
    List<Defense *>::iterator currentDefense = defenses.begin();

    //Algoritmo devorador para centro de extraccion
    while (!placed && !Cells.empty())
    {
        solution = Cells.back();
        Cells.pop_back();
        if (factible(defenses, *(*currentDefense), obstacles, mapHeight,
                     cellWidth, cellHeight, mapWidth, solution.row, solution.col, freeCells))
        {
            placed = true;
            freeCells[solution.row][solution.col] = false;
            (*currentDefense)->position = cellCenterToPosition(solution.row, solution.col, cellWidth, cellHeight);
        }
    }
    //Copia de los candidatos

    std::vector<Cell> AuxCells;

    for (i = 0; i < nCellsHeight; i++)
        for (j = 0; j < nCellsWidth; j++)
        {
            if (freeCells[i][j])
                AuxCells.push_back(Cell(i, j, cellValue(i, j, solution.row, solution.col, freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses)));
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

    Cells.clear();
    Cells = AuxCells;

    std::vector<Cell>::iterator it;
    int iterations;
    currentDefense++;

    while (currentDefense != defenses.end())
    {
        iterations = 0;
        placed = false;
        it = AuxCells.end();
        while (!placed && !Cells.empty())
        {
            iterations++;
            solution = Cells.back();
            Cells.pop_back();
            if (factible(defenses, *(*currentDefense), obstacles, mapHeight, cellWidth, cellHeight, mapWidth, solution.row, solution.col, freeCells))
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
        Cells.clear();
        Cells = AuxCells;
        currentDefense++;
    }
}















	/* ------------------------ NO TOCAR A PARTIR DE AQUI ----------------------- */
		++r;

    } while(c.tiempo() < 1.0);
    c.parar();
    std::cout << (nCellsWidth * nCellsHeight) << '\t' << c.tiempo() / r << '\t' << c.tiempo()*2 / r << '\t' << c.tiempo()*3 / r << '\t' << c.tiempo()*4 / r << std::endl;
}
