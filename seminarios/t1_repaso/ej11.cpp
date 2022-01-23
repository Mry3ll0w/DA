#include <iostream>
#include <list>
#include <vector>
using namespace std;//Avoid using std:: ....
std::list<int> restaurante(std::list<int>& personas, size_t aforo);

int main(){
    std::list<int> l = {3,2,4,1,5,2,5,6};
    for (auto i : restaurante(l,15)){
        std::cout << i << std::endl;
    }

return 0;
}

/*
    Formalizacion:

    Conjunto inicial (C) => Grupos de personas que llegan al restaurante
    
    Solucion (Solucion (S)==> Se ha llenado el restaurante o no quedan 
    personas esperando

    Seleccion ==> Selecciona la mesa mas factible

    Factible ==> Caben en las mesas dadas ?

    Objetivo ==> Minimizar el numero de mesas usadas

    Esta estrategia nos obliga a ser lo mas optima posible , ya que el enunciado nos obliga  a dar la mesa mas
    cercana al numero, ademas los greedy no dan siempre una solucion optima, si no una solucion cualquiera 


*/
int selecciona_mesa(int n){

    
    //Caso que el grupo sea igual a la capacidad de la mesa
    switch (n){
        
        case 2:
            return 2;
        break;

        case 4:
            return 4;
        break;

        case 6:
            return 6;
        break;

        default:
            if (n <= 2)
            {
                return 2;
            }
            else if ( n <= 4 && n > 2){
                return 4;
            }
            else if ( n <= 6 && n >4){
                return 6;
            }
            
        break;

    }

}

std::list<int> restaurante(std::list<int>& personas, size_t aforo){

    std::list<int> S,C=personas;

    while (!C.empty() && aforo > 0)
    {
        int g = C.front();
        C.pop_front();

        int mesa_selec = selecciona_mesa(g);
        if (aforo >= mesa_selec)//Si cabe entonces elige la mesa mas apropiada
        {
            S.push_back(mesa_selec);
            aforo-=mesa_selec;
        }
        

    }
    
return S;
}