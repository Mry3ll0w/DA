// ###### Config options ################


// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

using namespace Asedio;
/*
selected id ==> contiene el id de la defensa que se ha seleccionado 
*/
//Estaria bien crear una estructura para el almacenado de las defensas para el tsp

//codigo para rellenar la TSP (defensa (valor de la funcion dada) e id de la defensa)

//hacer algoritmo de recuperacion y rellenar la lista de selected id de las defensas

//Consideracion ==> hay que comprar la primera de la lista de defensas 

//como comprobar y tal ../simulador -level -l 3324 -ases 1000 -v

void DEF_LIB_EXPORTED selectDefenses(std::list<Defense*> defenses, unsigned int ases, 
std::list<int> &selectedIDs, float mapWidth, float mapHeight, std::list<Object*> obstacles) {
    //es necesario comprar la primera defensa siempre
    std::list<Defense*>::iterator it = defenses.begin() ;
    selectedIDs.push_back((*it)->id);
    ases -=(*it)->cost;

    unsigned int cost = 0;
    std::list<Defense*>::iterator it = defenses.begin();
    while(it != defenses.end()) {
        if(cost + (*it)->cost <= ases) {
            selectedIDs.push_back((*it)->id);
            cost += (*it)->cost;
        }
        ++it;
    }
}
