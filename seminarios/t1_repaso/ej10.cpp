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

std::vector<char> camino(std::vector<std::vector<char>>& m , const size_t& n_carriles);

int main(){

    std::vector<std::vector<char>> m= {
        {'L','v','v','c'},
        {'v','c','v','v'},
        {'c','v','v','c'},
        {'v','v','c','v'}
    };
    auto v = camino(m,4);
    for (auto i: v){
        std::cout << i << std::endl;
    }

    return 0;
}


size_t cuenta_movimientos(const std::vector<std::vector<char>>& m , const size_t& n_carriles,std::pair<int,int> pos){

    size_t movimientos=0;

    while (pos.second<=n_carriles)
    {
        if (
            m[pos.first][pos.second+1] == 'c' && 
            m[pos.first+1][pos.second+1]!= 'c' 
        )
        {
            movimientos++;
            //desplaza hacia abajo
            pos.first++;
            pos.second++;
        }
        else if(
            m[pos.first][pos.second+1] == 'c' && 
            m[pos.first-1][pos.second+1] != 'c' 
        ){
            movimientos++;
        }
        else if(m[pos.first][pos.second+1] != 'c'){
            pos.second++;
        }
        
    }
    
    return movimientos;
}

//Devuelve arriba o abajo segun toque
char selecciona_movimiento(std::pair<int, int>& c ,const std::vector<std::vector<char>>& m , const size_t& n_carriles){
    //Filas = carril y columnas ncontroles ++> se mueve arriba o abajo
    //seleccionamos mejor movimiento
    size_t mov_arr=0,mov_abajo=0;
    std::pair<int, int> ladron_a =c,ladron_ab =c;
    //caso arriba
    if(m[ladron_a.first-1][ladron_a.second+1] != 'c' && ladron_a.first < 1){
        ladron_a.second++;
        ladron_a.first--;
    }
    
    if(m[ladron_a.first+1][ladron_a.second+1] != 'c' && ladron_a.second < n_carriles){
        ladron_ab.second++;
        ladron_ab.first++;
    }

    mov_arr = cuenta_movimientos(m,n_carriles,ladron_a);
    mov_abajo = cuenta_movimientos(m,n_carriles,ladron_ab);

    if(mov_arr > mov_abajo){
        return 'a';
    }
    else if(mov_arr > mov_abajo){
        c = ladron_ab;
        return 'b';
    }
    else{
        c = ladron_a;
        return 'a';//En caso ser iguales de optimos sale arriba
    }

}

std::vector<char> camino(std::vector<std::vector<char>>& m , const size_t& n_carriles){

    std::vector<char>S;
    std::pair<int, int> c={0,0};
    char mov;
    while (c.second < n_carriles)//mientras que no se salga se sigue
    {
        mov = selecciona_movimiento(c,m,n_carriles);
        std::cout<<c.second<<std::endl;
        m[c.first][c.second]='L';
    }
    

return S;
} 