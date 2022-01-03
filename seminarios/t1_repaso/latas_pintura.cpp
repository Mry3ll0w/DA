#include <iostream>
#include <list>
using namespace std;//Avoid using std:: ....

const std::list<int> devorador( std::list<int> c, int metros); 


int main(){
    
    std::list<int> l={2,3,45,16,12,1,4};
    for(auto i : devorador(l,60))
        std::cout << i << ", ";

    std::cout << std::endl;
    return 0;
}

/* -------------------------------------------------------------------------- */
/*                                FORMALIZACION                               */
/* -------------------------------------------------------------------------- */
/*
    a) Analizar complejidad del algoritmo
        
        ordenacion ==> log n
        bucle n 
        O(n)

    b)Elementos
        
        Funcion de seleccion ==> c.back()//lista ordenada de mayor a menor (minimizar el uso de latas)
        Funcion Solución ==> Si el conjunto de entrada esta vacio o todos los metros se han pintado 
        Funcion de Factibilidad ==> Se gasta por completo la lata al pintar la superficie.
*/

const std::list<int> devorador(std::list<int> c, int metros){
    
    std::list<int> S;
    c.sort();//Funcion de ordenacion de orden logaritmico
    while (!c.empty() && metros > 0){
        
        int p = c.back();
        c.pop_back();
        if(metros - p > 0){
            S.push_back(p);
            metros-=p;
        }
            
    }

return S;
}