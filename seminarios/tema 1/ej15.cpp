#include <iostream>
#include <list>
#include <vector>
#include <list>
#include <map>

/*
Considere un videojuego clásico de desplazamiento vertical en el que el jugador debe evitar
que los asteroides que caen desde la parte superior de la pantalla colisionen con la nave
espacial que controla, y que se encuentra en la parte inferior de la pantalla. Los asteroides
se desplazan verticalmente, hacia la nave, y esta solo puede desplazarse horizontalmente
para evitarlos. Por otro lado, la pantalla se encuentra dividida en celdas de igual tamaño. En
cada momento, tanto la nave como cada uno de los asteroides ocupan una celda concreta.
La pantalla se actualiza a intervalos regulares, tras los que la nave puede desplazarse a una
de las dos columnas adyacentes para evitar a los asteroides, si es que no han colisionado ya
con ella. Diseñe un piloto automático para la nave.
*/
std::list<char> voraz(std::vector<std::vector<char>> mapa);

int main(){
    
return 0;
}

//algoritmo para asignar la valoracion en todo momento
std::vector<int> asignar_valoracion(std::vector<std::vector<char>> m, const size_t& d){
    std::vector<int>v(d);//vector vacio de x elementos 1 por columna
    
    for(size_t it_vec = 0;it_vec < d;++it_vec){//recorre el vector para guardar valoraciones
        
        for (size_t f = d-1;f >= 0 ; f--)
        {
            if(m[f][it_vec]=='a'){
                ++v[it_vec];
            }
        }
        
        
    }


}

//funcion objetivo ==> selecciona cual seria el mejor movimiento siguiente
std::pair<char,int> funcio_objetivo(std::vector<std::vector<char>> m, const int& d, std::pair<int,int> nave){
    std::vector<int>p_quieto, p_der, p_izq;
    
    //Comprobamos quieto
    if(m[nave.first][nave.second]!='a'){
        p_quieto = asignar_valoracion(m,d);
    }
    //Comprobamos derecha
    if(nave.second+1 < d-1){//No se sale al aplicar el operador

    }

    if(nave.second-1 > 0){

    }


}


std::list<char> voraz(std::vector<std::vector<char>> mapa, const size_t& dimensiones){
    
    std::vector<int>valoracion; // nos vale para valorar hacia donde movernos

return pos_final;
}