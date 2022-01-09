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


float bestRelation(List<Defense*> defenses)
{
    float best = 0;
    List<Defense*>::iterator it = defenses.begin();
    
    while(it != defenses.end())
    {
        if((*it)->damage / (*it)->health > best)
            best = (*it)->damage / (*it)->health;
        it++;
    }
    return best;
}

void DEF_LIB_EXPORTED calculateAdditionalCost(float **additionalCost, int cellsWidth, int cellsHeight, float mapWidth, float mapHeight, List<Object *> obstacles, List<Defense *> defenses)
{

    float cellWidth = mapWidth / cellsWidth;
    float cellHeight = mapHeight / cellsHeight;
    List<Defense*>::iterator it = defenses.begin();
    float bestDef = bestRelation(defenses), diff;

    for (int i = 0; i < cellsHeight; ++i)
    {
        for (int j = 0; j < cellsWidth; ++j)
        {
            Vector3 cellPosition = cellCenterToPosition(i, j, cellWidth, cellHeight);
            float cost = 0;
            while(it != defenses.end())
            {
                cost += (1/_distance(cellPosition, (*it)->position))*1000;
                diff = bestDef - (bestDef - (*it)->damage / (*it)->health);
                cost *= diff*100;
                it++;
            }
            it = defenses.begin();
            additionalCost[i][j] = cost;
        }
    }
}
/* -------------------------------------------------------------------------- */
/*                          IMPLEMENTACIONES PROPIAS                          */
/* -------------------------------------------------------------------------- */

std::pair<int,int> get_x_y(const Vector3 pos, float cellWidth, float cellHeight)
{
    //i_out = (int)(pos.y * 1.0f / cellHeight);
    //j_out = (int)(pos.x * 1.0f / cellWidth);

    return std::make_pair((int)(pos.x * 1.0f / cellWidth), (int)(pos.y /cellHeight));

}

//Nos sirve para comprobar si el nodo esta o no en la lista de visitados
bool existe_nodo(AStarNode *nodo, std::vector<AStarNode *> nodos)
{
    bool found = false;
    
    for(auto i = nodos.begin(); i != nodos.end() && !found; ++i){
        
        if (nodo == *i)
            found = true;
        
    }
    
    return found;
}

std::list<Vector3> recupera_camino(AStarNode *begin, AStarNode *destino)
{
    AStarNode *actual = destino;
    std::list<Vector3> path;

    //Insertamos la posicion del destino ya que para la obtencion del camino se 
    path.push_back(destino->position);

    //Recorremos en orden inverso
    for(;actual->parent != begin && destino->parent != NULL;actual=actual->parent)
        path.push_front(actual->position);

    return path;
}

int Heuristica_Manhattan(AStarNode *begin, AStarNode *target, float cellWidth, float cellHeight)
{
    int o_x, o_y, d_x, d_y, dist = 0;
    std::pair<int, int> parser;
    
    //Coordenadas de origen
    parser = get_x_y(begin->position, cellWidth, cellHeight);
    o_x = parser.first; o_y = parser.second;

    //Coordenadas de destino
    parser = get_x_y(target->position, cellWidth, cellHeight);
    d_x = parser.first; d_y = parser.second;

    dist = abs(o_x - d_x) + abs(o_y - d_y);
    return dist;
}

struct greaterComparator
{
    bool operator()(AStarNode* a, AStarNode* b)
    {
        return a->F > b->F;
    }
};

void DEF_LIB_EXPORTED calculatePath(AStarNode *originNode, AStarNode *targetNode, int cellsWidth, int cellsHeight, float mapWidth, float mapHeight, float **additionalCost, std::list<Vector3> &path)
{
    /* -------------------------------- VARIABLES ------------------------------- */
    std::pair<int, int> p;
    int maxIter = 100;
    AStarNode *current = originNode;
    std::vector<AStarNode *> opened, closed;
    bool found = false;
    List<AStarNode *>::iterator it;
    float dist;
    float cellWidth = mapWidth / cellsWidth;
    float cellHeight = mapHeight / cellsHeight;
    /* -------------------------------- ALGORITMO ------------------------------- */
    
    targetNode->parent = NULL;

    current->G = 0;
    current->H = Heuristica_Manhattan(current, targetNode, cellWidth, cellHeight);
    //Obtener posiciones dentro de la matriz
    p = get_x_y(current->position,cellWidth, cellHeight);
    current->F = current->G + current->H + additionalCost[p.first][p.second];

    opened.push_back(current);

    while (!found && !opened.empty())
    {
        current = opened.front();
        std::pop_heap(opened.begin(), opened.end(), greaterComparator());
        opened.pop_back();
        closed.push_back(current);
        if (current == targetNode)
        {
            found = true;
        }
        else
        {
            it = current->adjacents.begin();
            while (it != current->adjacents.end())
            {
                if (!existe_nodo((*it), closed))
                {
                    if (!existe_nodo((*it), opened))
                    {
                        (*it)->parent = current;
                        (*it)->G = current->G + _distance(current->position, (*it)->position);
                        (*it)->H = Heuristica_Manhattan((*it), targetNode, cellWidth, cellHeight);
                        
                        p = get_x_y((*it)->position,cellWidth, cellHeight);
                        (*it)->F = (*it)->G + (*it)->H + additionalCost[p.first][p.second];
                        
                        opened.push_back((*it));
                        std::push_heap(opened.begin(), opened.end(), greaterComparator());
                    }
                    else
                    {
                        dist = _distance(current->position, (*it)->position);
                        if ((*it)->G > current->G + dist)
                        {
                            (*it)->parent = current;
                            (*it)->G += dist;

                            p = get_x_y((*it)->position,cellWidth, cellHeight);
                            (*it)->F = (*it)->G + (*it)->H + + additionalCost[p.first][p.second];
                            
                            std::make_heap(opened.begin(), opened.end(), greaterComparator());
                        }
                    }
                }
                it++;
            }
        }
    }
    path = recupera_camino(originNode, targetNode);
}
