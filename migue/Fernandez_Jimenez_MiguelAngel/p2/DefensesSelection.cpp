// ###### Config options ################


// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"

using namespace Asedio;

float valDefensa(const Defense& def)
{
    float valor;

    valor = (def.damage*def.attacksPerSecond*def.health*def.range) / (def.dispersion);  //Mejor estrategia posible
    
    return valor;
}

void beneficioMaximo(std::vector<std::vector<float>>& TSP, std::list<Defense*> defenses, unsigned int ases)
{
    float valores[defenses.size() - 1];
    int costes[defenses.size() - 1];
    List<Defense*>::iterator it = defenses.begin();
    it++;

    //Relleno los vectores
    for(int i = 0; i < defenses.size()-1; i++)
    {
        costes[i] = (*it)->cost;
        valores[i] = valDefensa((**it));
        it++;
    }

    ases = ases - (*defenses.begin())->cost;
    for(int j = 0; j < ases+1; j++)
    {
        if (j < costes[0])
            TSP[0][j] = 0;
        else
            TSP[0][j] = valores[0];
    }
    for(int i = 1; i < defenses.size()-1; i++){
        for(int j = 0; j < ases+1; j++)
        {
            if(j < costes[i])
                TSP[i][j] = TSP[i-1][j];
            else
                TSP[i][j] = std::max(TSP[i-1][j], TSP[i-1][j-costes[i]] + valores[i]);
        }
    }
}

void defensasOptimas(std::list<Defense*> defenses, unsigned int ases, std::list<int>& selectedIDs, const std::vector<std::vector<float>>& spTable)
{
    int i = defenses.size() - 2, j = ases - (*defenses.begin())->cost;
    List<Defense*>::iterator it = defenses.end();

    it--;
    while(i > 0)
    {
        if(spTable[i][j] != spTable[i-1][j])
        {
            j = j - (*it)->cost;
            selectedIDs.push_back((*it)->id);
        }
        i--;
        it--;
    }
    if(spTable[0][j] != 0)
        selectedIDs.push_back((*it)->id);
}


void DEF_LIB_EXPORTED selectDefenses(std::list<Defense*> defenses, unsigned int ases, std::list<int> &selectedIDs
            , float mapWidth, float mapHeight, std::list<Object*> obstacles) {

    unsigned int cost = 0;
    List<Defense*>::iterator it = defenses.begin();
    std::vector<std::vector<float>> spTable(defenses.size()-1, std::vector<float>(ases-(*it)->cost+1));
    selectedIDs.push_back((*it)->id);
    it = defenses.begin();
    beneficioMaximo(spTable, defenses, ases);
    defensasOptimas(defenses, ases, selectedIDs, spTable);
}
