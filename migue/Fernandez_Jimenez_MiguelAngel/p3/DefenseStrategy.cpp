// ###### Config options ################

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include "cronometro.h"

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

bool factible(List<Defense *> defenses, const Defense &currentDef, List<Object *> obstacles, float mapHeight,
              float cellWidth, float cellHeight, float mapWidth, int row, int col, bool **freeCells, int count)
{
    bool fact;

    Vector3 posicion = cellCenterToPosition(row, col, cellWidth, cellHeight);

    if (posicion.x + currentDef.radio > mapWidth ||  //Se sale por la derecha
        posicion.x - currentDef.radio < 0 ||         //Se sale por la izquierda
        posicion.y + currentDef.radio > mapHeight || //Se sale por abajo
        posicion.y - currentDef.radio < 0)           //Se sale por arriba
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

    for (j = defenses.begin(); count > 0 && j != defenses.end(); j++)
    {
        //Si la distancia entre los centros es menor a la suma de los radios de la defensa actual y la que está colocada, colisionan
        if (_distance(posicion, (*j)->position) < (currentDef.radio + (*j)->radio))
            fact = false;
        count--;
    }

    return fact;
}

float defaultCellValue(int row, int col, bool **freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, List<Object *> obstacles, List<Defense *> defenses)
{

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;

    Vector3 cellPosition((col * cellWidth) + cellWidth * 0.5f, (row * cellHeight) + cellHeight * 0.5f, 0);

    float val = 0;
    for (List<Object *>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
    {
        val += _distance(cellPosition, (*it)->position);
    }

    return val;
}

struct CellValue
{
    int row, col;
    float value;
    CellValue(int r = 0, int c = 0, float v = 0) : row(r), col(c), value(v) {}
};

void insertion_sort(std::vector<CellValue> &v, int first, int last)
{
    int i, j;
    CellValue c;
    for (i = first + 1; i <= last; i++)
    {
        c = v[i];
        j = i - 1;
        while (j >= first && v[j].value > c.value)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = c;
    }
}

void fusion(std::vector<CellValue> &v, int i, int k, int j)
{
    int n = j - i + 1, p = i, q = k + 1, l;
    std::vector<CellValue> c;
    c.resize(v.size());

    for (l = 0; l < n; l++)
    {
        if (p <= k && (q > j || v[p].value <= v[q].value))
        {
            c[l] = v[p];
            p++;
        }
        else
        {
            c[l] = v[q];
            q++;
        }
    }
    for (l = 0; l < n; l++)
        v[i + l] = c[l];
}

void fusionSort(std::vector<CellValue> &v, int i, int j)
{
    int n = j - i + 1;
    int k;

    if (n <= 3)
        insertion_sort(v, i, j);
    else
    {
        k = i - 1 + n / 2;
        fusionSort(v, i, k);
        fusionSort(v, k + 1, j);
        fusion(v, i, k, j);
    }
}

int pivot(std::vector<CellValue> &v, int i, int j)
{
    int n = i, k;
    CellValue c = v[i];

    for (k = i + 1; k <= j; k++)
        if (v[k].value <= c.value)
        {
            n++;
            std::swap(v[n], v[k]);
        }
    v[i] = v[n];
    v[n] = c;

    return n;
}

void quickSort(std::vector<CellValue> &v, int i, int j)
{
    int n = j - i + 1;
    int p;

    if (n <= 3)
        insertion_sort(v, i, j);
    else
    {
        p = pivot(v, i, j);
        quickSort(v, i, p - 1);
        quickSort(v, p + 1, j);
    }
}

std::vector<CellValue>::iterator maxValue(std::vector<CellValue> &v)
{
    CellValue max = v.front();
    std::vector<CellValue>::iterator it, sol = v.begin();
    for (it = v.begin(); it != v.end(); it++)
    {
        if ((*it).value > max.value)
        {
            max = (*it);
            sol = it;
        }
    }
    return sol;
}

void copyMatrix(bool **&sol, bool **m, int cols, int rows)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            sol[i][j] = m[i][j];
}

bool operator<(CellValue a, CellValue b)
{
    return (a.value < b.value);
}

void DEF_LIB_EXPORTED placeDefenses3(bool **freeCells, int nCellsWidth, int nCellsHeight, float mapWidth, float mapHeight, List<Object *> obstacles, List<Defense *> defenses)
{

    float cellWidth = mapWidth / nCellsWidth;
    float cellHeight = mapHeight / nCellsHeight;

    cronometro c1, c2, c3, c4;
    long int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
    int maxAttemps = 1000;
    std::vector<CellValue> Cells, CellsBackup;

    int i, j, k;
    const double e_abs = 0.01, e_rel = 0.001;

    for (i = 0; i < nCellsHeight; i++)
        for (j = 0; j < nCellsWidth; j++)
        {
            if (freeCells[i][j])
                CellsBackup.push_back(CellValue(i, j, defaultCellValue(i, j, freeCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses)));
        }

    bool **candidateCells = new bool *[nCellsHeight];

    for (int i = 0; i < nCellsHeight; i++)
        candidateCells[i] = new bool[nCellsWidth];

    copyMatrix(candidateCells, freeCells, nCellsWidth, nCellsHeight);
    //Vector centro extr
    for (i = 0; i < nCellsHeight; i++)
        for (j = 0; j < nCellsWidth; j++)
        {
            if (candidateCells[i][j])
                Cells.push_back(CellValue(i, j, defaultCellValue(i, j, candidateCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses)));
        }

    bool placed = false;
    CellValue solution;
    List<Defense *>::iterator currentDefense = defenses.begin();

    quickSort(Cells, 0, Cells.size() - 1);

    //Algoritmo devorador para centro de extraccion
    while (!placed && !Cells.empty())
    {
        solution = Cells.back();
        Cells.pop_back();
        if (factible(defenses, *(*currentDefense), obstacles, mapHeight,
                     cellWidth, cellHeight, mapWidth, solution.row, solution.col, candidateCells, 0))
        {
            placed = true;
            candidateCells[solution.row][solution.col] = false;
            (*currentDefense)->position = cellCenterToPosition(solution.row, solution.col, cellWidth, cellHeight);
        }
    }
    //Copia de los candidatos

    std::vector<CellValue> AuxCells;

    for (i = 0; i < nCellsHeight; i++)
        for (j = 0; j < nCellsWidth; j++)
        {
            if (candidateCells[i][j])
                AuxCells.push_back(CellValue(i, j, defaultCellValue(i, j, candidateCells, nCellsWidth, nCellsHeight, mapWidth, mapHeight, obstacles, defenses)));
        }

    k = 0;

    quickSort(AuxCells, 0, AuxCells.size() - 1);
    Cells = AuxCells;

    std::vector<CellValue>::iterator it;
    int iterations, defensecount = 1;
    currentDefense++;
    std::vector<CellValue>::iterator eraser;

    while (currentDefense != defenses.end())
    {
        iterations = 0;
        placed = false;
        it = AuxCells.end();
        while (!placed && !Cells.empty())   //Caso peor -> orden n (n = nº celdas)
        {
            iterations++;
            solution = Cells.back();
            Cells.pop_back();
            if (factible(defenses, *(*currentDefense), obstacles, mapHeight, cellWidth, cellHeight, mapWidth, solution.row, solution.col, candidateCells, defensecount))
            {
                //std::cout << "Defensa: " << (*currentDefense)->id << " Celda: " << solution.row << "," << solution.col << " Valor: " << solution.value << std::endl;
                placed = true;
                defensecount++;
                (*currentDefense)->position = cellCenterToPosition(solution.row, solution.col, cellWidth, cellHeight);
                while (iterations > 0)
                {
                    it--;
                    iterations--;
                }
                AuxCells.erase(it);
            }
        }
        Cells = AuxCells;
        currentDefense++;
    }
    Cells.clear();
    AuxCells.clear();
}
