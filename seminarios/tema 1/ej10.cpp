#include<iostream>
#include<list>
#include<vector>

std::list<char> voraz(std::vector<std::vector<char>> matriz, const size_t N);

int main(){

return 0;
}

/*
Deseamos atravesar una autopista de m carriles en la que la policía ha establecido n puntos
de control. En cada uno de ellos ha colocado puestos de control ocupando uno o más de los
carriles, pero no todos.
Conocemos, para cada punto de control, en qué carriles están situados los puestos de control. Para atravesar la autopista sin ser interceptados debemos cruzar cada punto de control
por un carril en el que no esté la policía. El problema es que debemos realizar el mínimo número posible de cambios de carril (un único cambio de carril puede implicar cruzar varios
carriles) a fin de no levantar sospechas.
Diseñe un algoritmo que calcule el camino óptimo, es decir, que diga por qué carril hay que
pasar en cada punto de control para minimizar el número de cambios de carril.
El algoritmo recibirá una matriz binaria de m filas y n columnas en la que cada elemento
informará sobre la existencia de un puesto de control en un carril y un punto de control
dados. Como resultado devolverá un vector de n elementos indicando el carril elegido en
cada punto de control.
*/

std::list<char> voraz(std::vector<std::vector<char>> matriz, const size_t N){
    
}