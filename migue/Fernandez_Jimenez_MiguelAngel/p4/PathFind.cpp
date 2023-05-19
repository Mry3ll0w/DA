// ###### Config options ################

#define PRINT_PATHS 1

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

#ifdef PRINT_PATHS
#include "ppm.h"
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

float best_option(List<Defense*> defenses)
{
    List<Defense*>::iterator i = defenses.begin();
    float best_defense = 0;
    
    while(i != defenses.end())
    {
        if((*i)->damage / (*i)->health > best_defense)
            best_defense = (*i)->damage / (*i)->health;
        i++;
    }
    return best_defense;
}

void DEF_LIB_EXPORTED calculateaddCost(float **addCost, int cellsWidth, int cellsHeight, float mapWidth, float mapHeight, List<Object *> obstacles, List<Defense *> defenses)
{

    float cellWidth = mapWidth / cellsWidth;
    float cellHeight = mapHeight / cellsHeight;
    List<Defense*>::iterator i = defenses.begin();
    float bestDefense = best_option(defenses), dist;

    for (int k = 0; k < cellsHeight; ++k)
    {
        for (int j = 0; j < cellsWidth; ++j)
        {
            Vector3 cellPosition = cellCenterToPosition(k, j, cellWidth, cellHeight);
            float cost = 0;
            while(i != defenses.end())
            {
                cost += (1/_distance(cellPosition, (*i)->position))*1000;
                dist = bestDefense - (bestDefense - (*i)->damage / (*i)->health);
                cost *= dist*100;
                i++;
            }
            i = defenses.begin();
            addCost[k][j] = cost;
        }
    }
}

bool searchNode(AStarNode *node, std::vector<AStarNode *> nodeList)
{
    std::vector<AStarNode *>::iterator i = nodeList.begin();
    bool nodeFound = false;

    while (i != nodeList.end() && !nodeFound)
    {
        if (node == *i)
            nodeFound = true;
        i++;
    }

    return nodeFound;
}

List<Vector3> recoverPath(AStarNode *nodeBeg, AStarNode *nodeObj)
{
    AStarNode *actual = nodeObj;
    List<Vector3> pathFound;
    pathFound.push_back(nodeObj->position);

    while (actual->parent != nodeBeg && nodeObj->parent != NULL)
    {
        actual = actual->parent;
        pathFound.push_front(actual->position);
    }
    return pathFound;
}

int Manhattan(AStarNode *nodeBeg, AStarNode *nodeObj, float cellWidth, float cellHeight)
{
    int Row, Col, rowObj, colObj, dist = 0;
    positionToCell(nodeBeg->position, Row, Col, cellWidth, cellHeight);
    positionToCell(nodeObj->position, rowObj, colObj, cellWidth, cellHeight);
    dist = abs(Row - rowObj) + abs(Col - colObj);

    return dist;
}

struct bestChoice
{
    bool operator()(AStarNode* x, AStarNode* y)
    {
        return x->F > y->F;
    }
};

void DEF_LIB_EXPORTED calculatePath(AStarNode *nodeBeg, AStarNode *nodeObj, int cellsWidth, int cellsHeight, float mapWidth, float mapHeight, float **addCost, std::list<Vector3> &path)
{

    int x, y;
    AStarNode *actual = nodeBeg;
    std::vector<AStarNode *> open, close;
    List<AStarNode *>::iterator i;
    bool nodeFound = false;
    float cellWidth = mapWidth / cellsWidth;
    float cellHeight = mapHeight / cellsHeight;
    float distance;
    actual->G = 0;
    actual->H = Manhattan(actual, nodeObj, cellWidth, cellHeight);
    positionToCell(actual->position, x, y, cellWidth, cellHeight);
    actual->F = actual->G + actual->H + addCost[x][y];
    nodeObj->parent = NULL;

    open.push_back(actual);

    while (!nodeFound && !open.empty())
    {
        actual = open.front();
        std::pop_heap(open.begin(), open.end(), bestChoice());
        open.pop_back();
        close.push_back(actual);
        if (actual == nodeObj)
        {
            nodeFound = true;
        }
        else
        {
            i = actual->adjacents.begin();
            while (i != actual->adjacents.end())
            {
                if (!searchNode((*i), close))
                {
                    if (!searchNode((*i), open))
                    {
                        (*i)->parent = actual;
                        (*i)->G = actual->G + _distance(actual->position, (*i)->position);
                        (*i)->H = Manhattan((*i), nodeObj, cellWidth, cellHeight);
                        positionToCell((*i)->position, x, y, cellWidth, cellHeight);
                        (*i)->F = (*i)->G + (*i)->H + addCost[x][y];
                        open.push_back((*i));
                        std::push_heap(open.begin(), open.end(), bestChoice());
                    }
                    else
                    {
                        distance = _distance(actual->position, (*i)->position);
                        if ((*i)->G > actual->G + distance)
                        {
                            (*i)->parent = actual;
                            (*i)->G += distance;
                            positionToCell((*i)->position, x, y, cellWidth, cellHeight);
                            (*i)->F = (*i)->G + (*i)->H + + addCost[x][y];
                            std::make_heap(open.begin(), open.end(), bestChoice());
                        }
                    }
                }
                i++;
            }
        }
    }
    path = recoverPath(nodeBeg, nodeObj);
}
