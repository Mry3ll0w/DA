#include <iostream>
#include <vector>
#include <list>
#define N 3 //Size para la matriz del tablero
using namespace std;//Avoid using std:: ....

int main(){
    
return 0;
}

/*
Diseñe un algoritmo devorador que encuentre la mejor posición para colocar una piedra en
el juego Gomoku a partir de un estado concreto del tablero.1 Necesitará diseñar una función
auxiliar, en-línea(c,i, j), que determine el máximo número de piedras que se conectan en
línea en cualquiera de las direcciones al colocar una piedra de color c (blanca o negra) en la
intersección (i, j). 

a) Describa los elementos que lo identifican como perteneciente al esquema
general de los algoritmos devoradores. 

    Factibilidad ==> Hay hueco en la posicion devuelta por maximo ?
    Objetivo ==> maximizar el numero de fichas conectadas del mismo color en cada movimiento
    Solucion ==>Obtener la mejor posicion para colocar la piedra
    Conjunto inicial ==> tablero de entrada, con el juego en una situacion concreta

b) Analice su complejidad
*/

int cuenta_seguidas(pair< int , int> coordenada, char color, vector<vector<char>> tablero){
    int cont;
    
    //Cuenta a su derecha (en la misma fila)
    bool token = true;//Empezamos en la siguiente de la coordenada dada
    
    for (size_t i = coordenada.second+1; i < N && token; i++)
    {
        if(tablero[coordenada.first][i]!=color)
            token = false;
        cont++;
    }
    //reset de token
    token = true;
    //Contamos los de la izquierda, a partir del anterior
    for (size_t i = coordenada.second-1; i >= 0  && token; i++)
    {
        if(tablero[coordenada.first][i]!=color)
            token = false;
        cont++;
    }

    token = true;

    //Contamos hacia arriba, empezando por el inmmediatamente superior
    for (size_t i = coordenada.first-1; i >= 0 && token; i++)
    {
        if(tablero[coordenada.first][i]!=color)
            token = false;
        cont++;
    }

    //contamos los de abajo
    token = true;

    for (size_t i = coordenada.first+1; i < N && token; i++)
    {
        if(tablero[coordenada.first][i]!=color)
            token = false;
        cont++;
    }


return cont;
}

pair<int, int > en_linea (vector<vector<char>> tablero, char color){

    std::list<int, pair< int , int > > posiciones;
    for (size_t i = 0; i < N; i++)
    {
        for(size_t j = 0; j < N; j++){
            
            if(tablero[i][j]=='#'){//Si es == a # esta vacia
                
                pair<int, pair<int,int> >p = {cuenta_seguidas(std::make_pair(i,j),color,tablero),{i,j}};
                posiciones.emplace_back(p);

            }

        }
    }
    
    posiciones.sort();//Ordeno de menor a mayor usando el cuenta seguidas como indice

return posiciones.back();
}


std::pair<int , int> gomoku (vector<vector<char>> tablero, char color){
    
    return en_linea(tablero, color);//devolvemos la mejor posicion para colocar la ficha del color dado en el tablero
     
}