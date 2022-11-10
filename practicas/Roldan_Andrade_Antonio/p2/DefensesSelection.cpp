// ###### Config options ################

// #######################################

#define BUILDING_DEF_STRATEGY_LIB 1

#include "../simulador/Asedio.h"
#include "../simulador/Defense.h"
#include <vector>

using namespace Asedio;
/*
selected id ==> contiene el id de la defensa que se ha seleccionado
*/
// Estaria bien crear una estructura para el almacenado de las defensas para el tsp

// codigo para rellenar la TSP (defensa (valor de la funcion dada) e id de la defensa)

// hacer algoritmo de recuperacion y rellenar la lista de selected id de las defensas

// Consideracion ==> hay que comprar la primera de la lista de defensas

// como comprobar y tal ../simulador -level -l 3324 -ases 1000 -v

// Formalice una funcion que asigne un valor a la funcion que asigna un determinado valor a cada uno
// de los tipos de defensas

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 1                                */
/* -------------------------------------------------------------------------- */
// para el almacenado de las defensas , usaremos un struct para hacer uso del metodo sort de list
struct defensa_valoracion
{

    Defense *d;

    float valoracion;

    defensa_valoracion(Defense *d_, float v) : d(d_), valoracion(v) {}

    // ordenaremos segun el coste de la defensa (almacenado en defensa.cost) para una correcta ordenacion de los datos
    bool operator<(const defensa_valoracion &b)
    {

        return d->cost < b.d->cost;
    }
};

// asigna el valor de cada una de las defensas
std::list<defensa_valoracion> defense_value(std::list<Defense *> &defenses)
{
    std::list<defensa_valoracion> def_value_list;

    // el criterio para seleccionar cual es mejor es la suma del daño + la salud + el alcance menos el coste
    for (auto i : defenses)
    {
        def_value_list.push_back(defensa_valoracion(i, (i->damage + i->health + i->range) - i->cost));
    }

    return def_value_list;
}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 2                                */
/* -------------------------------------------------------------------------- */

// 2) Describa la estructura o estructuras usadas para representar la tabla de subproblemas resueltos.
// se necesitaria trabajar con iteradores que mueva a la vez la matriz y la lista de defensa valoracion

// Aun teniendo el coste ya almacenado en defensa usaremos esta struct para poder llamar al sort de lista
// permitiendo así una ordenacion más óptima (de orden logaritmica).
struct TSP
{

    // La matriz almacenara la tabla de subproblemas resueltos
    std::vector<std::vector<int>> matriz_tsp;

    // Constructor de struct (asigna un tamaño maximo a las filas y columnas de la TSP)
    TSP(const int &max_ases, std::list<defensa_valoracion> &list_defensas_coste);

    // Contiene la lista de defensas junto con su valoracion para realizar el algortimo de la mochila
    std::list<defensa_valoracion> def_val_list;
};

TSP::TSP(const int &max_ases, std::list<defensa_valoracion> &list_defensas_coste) : def_val_list(list_defensas_coste)
{
    // Realiza la reserva de espacios (en este caso es limitarlo para rellenar con valores predeterminados)

    matriz_tsp = std::vector<std::vector<int>>(list_defensas_coste.size(), std::vector<int>(max_ases + 1));
    // Mediante el constructor de cada uno de los vectores que compone la matriz inicializamos las filas y columnas
    // el n de filas viene dado por la capacidad de la mochila + 1 y el numero de columnas viene dado por el nº de defensas

    // ordenamos la lista de defensas_coste para poder tratarla con mayor optimizacion
    def_val_list.sort();

    // Rellenamos la matriz TSP

    // Para poder trabajar con la matriz con comodidad usaremos un vector de pairs donde el primero sera el coste y el segundo la valoracion
    std::vector<std::pair<int, int>> v_coste_valor;

    for (auto i : def_val_list) // Lo subimos sin comprobar ordenacion, ya que esta viene ordenada
    {
        v_coste_valor.push_back(std::make_pair(i.d->cost, i.valoracion));
    }

    // 1) Inicializamos la fila inicial de la matriz_tsp

    // comenzamos la insercion de la fila de 0 capacidad
    for (int j = 0; j < max_ases + 1; ++j)
    {

        if (j < def_val_list.begin()->d->cost) // Comprobamos que la primera defensa se pueda pagar con 0 ases
        {
            matriz_tsp[0][j] = 0;
        }
        else
        {                                                        // En caso de poder pagarla guardamos la valoracion de la misma
            matriz_tsp[0][j] = def_val_list.begin()->valoracion; // metemos el valor del elemento que cabe en 0
        }
    }

    // 2) Rellenamos el resto de filas y columnas

    // comenzaremos en el segundo elemento ya que el primero la matriz ya esta relleno
    for (int i = 1; i < def_val_list.size(); i++)
    {

        for (int j = 0; j < max_ases + 1; j++)
        {

            if (j < v_coste_valor[i].first)
            {
                matriz_tsp[i][j] = matriz_tsp[i - 1][j]; // si el coste es mayor que el nº de ases, metemos el anterior
            }
            else
            {

                matriz_tsp[i][j] = std::max(matriz_tsp[i - 1][j], matriz_tsp[i - 1][j - v_coste_valor[i].first] + v_coste_valor[i].second);
            }
        }
    }
}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 3                                */
/* -------------------------------------------------------------------------- */

// Recibe la struct tsp (que tiene la lista de defensas a colocar etc) y el maximo numero de ases
// Se asume que la TSP ya se ha creado e inicializado con exito (previamente en su constructor)
int max_beneficio(TSP &tsp, const int &max_ases)
{

    return tsp.matriz_tsp[tsp.def_val_list.size() - 1][max_ases]; // devolvemos el ultimo elemento de la matriz que contiene el max valor
}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 4                                */
/* -------------------------------------------------------------------------- */
std::list<Defense *> recupera_defensas(const std::vector<std::vector<int>> &tsp,
                                       const std::list<defensa_valoracion> &def_val, const int &filas, const int &cols, std::list<Defense *> defenses)
{

    // Almacenara las defensas que se han usado
    std::list<Defense *> sol;

    int i = filas - 2;
    int j = cols - (*defenses.begin())->cost; // Tenemos que eliminar el coste de la primera defense (centro de extraccion), que ademas se añade en cualquier caso

    List<Defense *>::iterator it = defenses.end();

    it--; // Iniciamos en la posicion anterior a la ultima defensa (seria fin - 1)

    // Se Recorrera inversamente ya que partimos del beneficio maximo que se encuentra en
    // la ultima posicion de la matriz
    while (i > 0)
    {
        if (tsp[i][j] != tsp[i - 1][j])
        {
            j = j - (*it)->cost;
            sol.push_back(*(it));
        }
        i--;
        it--;
    }
    if (tsp[0][j] != 0)       // En caso de que la primera posicion de la fila 0 sea != de 0 significa que la existe una defensa que tiene coste 0 y entrara en la lista
        sol.push_back((*it)); // Insertamos dicha defensa

    return sol; // Devolvemos la lista de defensas
}

/* -------------------------------------------------------------------------- */
/*                     ALGORITMO DE SELECCION DE DEFENSAS                     */
/* -------------------------------------------------------------------------- */

void DEF_LIB_EXPORTED selectDefenses(std::list<Defense *> defenses, unsigned int ases,
                                     std::list<int> &selectedIDs, float mapWidth, float mapHeight, std::list<Object *> obstacles)
{

    // Asignamos ahora a cada defensa una valoracion
    std::list<defensa_valoracion> def_v;
    def_v = defense_value(defenses);

    // Creamos un objeto de la struct TSP para obtener el maximo beneficio y la matriz de subproblemas resueltos
    TSP str_tsp(ases, def_v);

    // Llamaremos ahora a la funcion que rellena la TSP y nos da el maximo beneficio
    int benef_max = max_beneficio(str_tsp, ases);

    /* ---- algoritmo para la insercion y seleccion de las defensas a colocar --- */

    // Para colocar de forma correcta sin modificar el centro de extraccion creamos esta lista
    std::list<Defense *> ordered_defenses;

    // Ordenamos las defensas
    ordered_defenses = recupera_defensas(str_tsp.matriz_tsp, def_v, def_v.size(), ases, defenses);

    // Metemos en la lista de IDs seleccionados la Defensa 0 , ya que siempre debe ser colocada
    unsigned int cost = 0;
    selectedIDs.push_back((*defenses.begin())->id);
    cost -= (*defenses.begin())->cost; // Actualizamos el coste de colocar esta misma

    // Creamos el iterador de las defensas ordenadas y las colocamos
    std::list<Defense *>::iterator it = ordered_defenses.begin();

    while (it != ordered_defenses.end())
    {
        if (cost + (*it)->cost <= ases)
        {
            selectedIDs.push_back((*it)->id);
            cost += (*it)->cost;
        }
        ++it;
    }
}
