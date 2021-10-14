#include <iostream>
#include <list>
using namespace std;//Avoid using std:: ....
std::list<int> greedy_latas(std::list<int>&c, size_t sup);
int main(){
    std::list<int> latas= {2,7,12,8,9};
    size_t N = latas.size();//contiene el numero de latas
    int sup = 29;
    std::list<int> sol = greedy_latas(latas,sup);
    std::cout << "Latas usadas: ";
    for(auto i: sol){
        std::cout << i <<", ";
    }
    std::cout <<std::endl;

    return 0;
}

/* FORMALIZACION
Conjunto inicial: N latas de x capacidad en litros
Funcion Solución: ¿Se ha pintado la superficie?
Funcion de Seleccion: La lata de menor capacidad, para poder gastarla.
Funcion de Factibilidad: Se gasta por completo la lata al pintar la superficie.
Funcion Objetivo: Latas que se han gastado por completo
Objetivo: maximizar el uso de las latas
*/
//funcion de seleccion
int funcion_seleccion(const std::list<int> &C){
    return C.front();
}
//funcion factibilidad
int funcion_factibilidad(int p, int sup){
    return (sup-p)>0; // si es mayor que 0 entonces sera viable
}

//Algoritmo greedy
std::list<int> greedy_latas(std::list<int>&c, size_t sup) {
    int p;
    std::list<int> S;
    std::list<int> C = c;
    C.sort();
    
    while (C.size() > 0 && sup > 0) {
        p = funcion_seleccion(C);
        C.erase(C.begin());//Poda del elemento seleccionado

        if (funcion_factibilidad(p,sup))//si es factible
        {
            S.insert(S.end(),p);
            sup-=p;
        }
        else{
            sup = 0;
        }
        
    }
    return S;
}
