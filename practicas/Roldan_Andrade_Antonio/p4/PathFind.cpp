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

Vector3 cellCenterToPosition(int i, int j, float cellWidth, float cellHeight){ 
    return Vector3((j * cellWidth) + cellWidth * 0.5f, (i * cellHeight) + cellHeight * 0.5f, 0); 
}

void DEF_LIB_EXPORTED calculateAdditionalCost(float** additionalCost
                   , int cellsWidth, int cellsHeight, float mapWidth, float mapHeight
                   , List<Object*> obstacles, List<Defense*> defenses) {

    float cellWidth = mapWidth / cellsWidth;
    float cellHeight = mapHeight / cellsHeight;

    for(int i = 0 ; i < cellsHeight ; ++i) {
        for(int j = 0 ; j < cellsWidth ; ++j) {
            Vector3 cellPosition = cellCenterToPosition(i, j, cellWidth, cellHeight);
            float cost = 0;
            if( (i+j) % 2 == 0 ) {
                cost = cellWidth * 100;
            }
            
            additionalCost[i][j] = cost;
        }
    }
}

/* -------------------------------------------------------------------------- */
/*                          IMPLEMENTACIONES PROPIAS                          */
/* -------------------------------------------------------------------------- */

//Devuelve las posiciones x e y que tiene un punto p en el mapa
std::pair<int,int> localiza_celdas(const Vector3& p, const float& cellWidth, const float& cellHeight){
    return std::make_pair((int)(p.x/cellWidth),(int)(p.y/cellHeight));
}

//Para calcular la heuristica usaremos la distancia manhattan entre el nodo origen y el nodo final
int heuristica_manhattan(const AStarNode* o, const AStarNode* d, const float& cellWidth, const float& cellHeight){

    int row_origen,row_destino,col_origen,col_destino;
    //Obtenemos la celda en la que estan ambas
    std::pair<int,int> c_or,c_dest;
    c_or = localiza_celdas(o->position,cellWidth,cellHeight);   
    c_dest= localiza_celdas(d->position,cellWidth,cellHeight);

    return abs(c_or.first-c_dest.first)+(c_or.second-c_dest.second); //Devolvemos la distancia existente  

}

//Busqueda de nodos dentro de una lista de nodos
bool existe_nodo(AStarNode *node, std::vector<AStarNode *>& lista)
{
    bool found = false;
    
    for(auto i : lista){
        if (node == i)
            found = true; break; // si la encuentra sale de la busqueda
    }

    return found;
}

//Necesitamos recuperar el camino que se recorre desde el nodo origen al nodo final
std::list<Vector3> recupera_camino(AStarNode *origen, AStarNode *final)
{
    AStarNode *it = final;

    std::list<Vector3> camino;

    camino.push_back(final->position);

    //Recorremos a la inversa el camino comprobando los padres
    for (AStarNode * it = final ; it->parent != origen && final->parent != NULL; it = it->parent)
    {
        camino.push_front(it->position);
    }
    
    return camino;
}

/* -------------------------------------------------------------------------- */
/*                                cambiar !!!!!                               */
/* -------------------------------------------------------------------------- */
struct greaterComparator
{
    bool operator()(AStarNode* a, AStarNode* b)
    {
        return a->F > b->F;
    }
};


/* -------------------------------------------------------------------------- */
/*                          ALGORITMO DE BUSQUEDA A*                          */
/* -------------------------------------------------------------------------- */
void DEF_LIB_EXPORTED calculatePath(AStarNode *originNode, AStarNode *targetNode, int cellsWidth, int cellsHeight, float mapWidth, float mapHeight, float **additionalCost, std::list<Vector3> &path)
{

    int maxIter = 100;
    AStarNode *current = originNode;
    std::vector<AStarNode *> opened, closed;
    bool found = false;
    List<AStarNode *>::iterator it;
    float dist;
    float cellWidth = mapWidth / cellsWidth;
    float cellHeight = mapHeight / cellsHeight;
    targetNode->parent = NULL;

    current->G = 0;
    current->H = heuristica_manhattan(current, targetNode, cellWidth, cellHeight);
    
    current->F = current->G + current->H + additionalCost[localiza_celdas(current->position, cellWidth, cellHeight).first]
    [localiza_celdas(current->position, cellWidth, cellHeight).second];

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
                        (*it)->H = heuristica_manhattan((*it), targetNode, cellWidth, cellHeight);
                        
                        std::pair<int, int> p = localiza_celdas((*it)->position,cellWidth, cellHeight);
                        
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
                            std::pair<int,int> p = localiza_celdas((*it)->position, cellWidth, cellHeight);
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
