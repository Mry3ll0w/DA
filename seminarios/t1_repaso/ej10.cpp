/*
Deseamos atravesar una autopista de m carriles en la que la policía ha establecido n puntos
de control. En cada uno de ellos ha colocado puestos de control ocupando uno o más de los
carriles, pero no todos.
Conocemos, para cada punto de control, en qué carriles están situados los puestos de control. Para atravesar la autopista sin ser interceptados debemos cruzar cada punto de control
por un carril en el que no esté la policía. El problema es que debemos realizar el mínimo número posible de cambios de carril (un único cambio de carril puede implicar cruzar varios
carriles) a fin de no levantar sospechas.
Diseñe un algoritmo que calcule el camino óptimo, es decir, que diga por qué carril hay que
pasar en cada punto de control para minimizar el número de cambios de carril.

El algoritmo recibirá una matriz binaria de m filas y n columnas en la que cada elemento
informará sobre la existencia de un puesto de control en un carril y un punto de control
dados. Como resultado devolverá un vector de n elementos indicando el carril elegido en
cada punto de control.

*/

#include <iostream>
#include <vector>

int main(){

    return 0;
}

//Devuelve arriba o abajo segun toque
char selecciona_movimiento(std::pair<int, int>& c ,const std::vector<std::vector<char>>& m , const size_t& n_carriles){
    //Filas = carril y columnas ncontroles ++> se mueve arriba o abajo
    //seleccionamos mejor movimiento
    size_t mov_arr=0,mov_abajo=0;
    std::pair<int, int> ladron =c;
    //caso arriba
    while(ladron.second < n_carriles ){

        if(ladron.first <= 0){
            mov_arr=(size_t)-1;  break;//no puedes ir hacia arriba, maximo a mov arr
        } 
        else{
            if(m[ladron.first][ladron.second+1] == 'c'&& m[ladron.first-1][ladron.second+1] != 'c'){
                mov_arr++;
                ladron.first--;
                ladron.second++;
            }
            else{
                ladron.second++;//no hay que mover hacia arriba por tanto sal
            }
        }

    }
    ladron = c;//reset para comprobar los abajo

    while(ladron.second < n_carriles ){

        if(ladron.first >= n_carriles){
            mov_arr=(size_t)-1;  break;//no puedes ir hacia abajo, maximo a mov arr
        } 
        else{
            if(m[ladron.first][ladron.second+1] == 'c' && m[ladron.first+1][ladron.second+1] != 'c'){
                mov_abajo++;
                ladron.first++;
                ladron.second++;
            }
            else{
                ladron.second++;//no hay que mover hacia arriba por tanto sal
            }
        }

    }

    if(mov_arr > mov_abajo){
        return 'a';
    }
    else{
        return 'b';
    }

}

std::vector<char> camino(const std::vector<std::vector<char>>& m , const size_t& n_carriles){

    std::vector<char>S;
    std::pair<int, int> c={0,0};
    char mov;
    while (c.second < n_carriles)//mientras que no se salga se sigue
    {
        mov = selecciona_movimiento(c,m,n_carriles);
        c.second++;
    }
    


return S;
} 