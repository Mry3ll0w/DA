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

Vector3 cellCenterToPosition(int i, int j, float cellWidth, float cellHeight)
{
    return Vector3((j * cellWidth) + cellWidth * 0.5f, (i * cellHeight) + cellHeight * 0.5f, 0);
}

void positionToCell(const Vector3 pos, int &i_out, int &j_out, float cellWidth, float cellHeight)
{
    i_out = (int)(pos.y * 1.0f / cellHeight);
    j_out = (int)(pos.x * 1.0f / cellWidth);
}

float cellValue(int row, int col, int exRow, int exCol, bool **freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, List<Object *> obstacles, List<Defense *> defenses)
{

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;
    Vector3 posicion = cellCenterToPosition(row, col, cellWidth, cellHeight);
    Vector3 bestPos = cellCenterToPosition(exRow, exCol, cellWidth, cellHeight);
    float value;

    value = bestPos.length() - _distance(posicion, bestPos);

    if (_distance(bestPos, posicion) > 3 * (*(defenses.back())).radio)
        value = value * 0.25;

    return value;
}

float cellValueCenter(int row, int col, bool **freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, List<Object *> obstacles)
{
    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;
    int bestRow = nCellsHeight / 2, bestCol = nCellsWidth / 2;
    Vector3 posicion = cellCenterToPosition(row, col, cellWidth, cellHeight);
    Vector3 bestPos = cellCenterToPosition(bestRow, bestCol, cellWidth, cellHeight);
    float value;

    value = bestPos.length() - _distance(posicion, bestPos);

    if (row < 3 || row > nCellsHeight - 3 || col > nCellsWidth - 3 || col < 3)
        value = value * 0.01;

    return value;
}

bool factible(List<Defense *> defenses, const Defense &currentDef, List<Object *> obstacles, float mapHeight,
              float cellWidth, float cellHeight, float mapWidth, int row, int col, bool **freeCells)
{
    bool fact;

    Vector3 posicion = cellCenterToPosition(row, col, cellWidth, cellHeight);

    if (posicion.x + currentDef.radio > mapWidth ||  
        posicion.x - currentDef.radio < 0 ||         
        posicion.y + currentDef.radio > mapHeight || 
        posicion.y - currentDef.radio < 0)           
        fact = false;
    else
        fact = true;

    List<Object *>::iterator i;

    for (i = obstacles.begin(); i != obstacles.end(); i++)
    {
        //Si la distancia entre los centros es menor a la suma de los radios de la defensa y el obstáculo, colisionan
        if (_distance(posicion, (*i)->position) < (currentDef.radio + (*i)->radio))
            fact = false;
    }

    List<Defense *>::iterator j;

    for (j = defenses.begin(); j != defenses.end(); j++)
    {
        //Si la distancia entre los centros es menor a la suma de los radios de la defensa actual y la que está colocada, colisionan
        if (_distance(posicion, (*j)->position) < (currentDef.radio + (*j)->radio))
            fact = false;
    }

    return fact;
}

struct Cell
{
    int row, col;
    float value;
    Cell(int r = 0, int c = 0, float v = 0) : row(r), col(c), value(v) {}
};

Cell copyCell(Cell c)
{
    return Cell(c.row, c.col, c.value);
}

void DEF_LIB_EXPORTED placeDefenses(bool **freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, std::list<Object *> obstacles, std::list<Defense *> defenses)
{

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;

    int maxAttemps = 1000;
    std::vector<Cell> Cells;
    int i, j, k;
    float aux;
    Cell auxCell;

    //Algoritmo centro extracción
    for (i = 0; i < nCellsHeight; i++)
        for (j = 0; j < nCellsWidth; j++)
        {
            if (freeCells[i][j])
                Cells.push_back(Cell(i, j, cellValueCenter(i, j, freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles)));
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
