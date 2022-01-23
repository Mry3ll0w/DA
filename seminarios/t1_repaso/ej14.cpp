#include <iostream>
#include <list>
#include <algorithm>
using namespace std;//Avoid using std:: ....
std::list<int> fontanero(std::list<int>& secciones, int longitud);
int main(){
    list<int> tramos = {2,56,1,23,4,10};
    cout<<"Secciones que va a necesitar: "<<std::endl;
    for (auto i : fontanero(tramos,78)){
        
        cout<<i<<", ";
    }
    
    std::cout<<std::endl;
return 0;
}

/*
Un fontanero dispone de varios segmentos de tubo de distintas longitudes.
Diseñe un algoritmo que, siguiendo una estrategia devoradora, minimice el número de uniones necesarias
para construir una única tubería de longitud l. El fontanero puede realizar los cortes en los
tubos que considere oportunos. Analice la complejidad del algoritmo.
*/
std::list<int> fontanero(std::list<int>& secciones, int longitud){
    
    std::list<int> S,C=secciones;
    C.sort();//de menor a mayor, por tanto si quiero minimizar, hay que reversear
    std::reverse(C.begin(),C.end());

    while (!C.empty() && longitud > 0 )
    {
        int tramo = C.front();
        C.pop_front();

        if (longitud >= tramo)
        {
            longitud -=tramo;
            S.push_back(tramo);
        }
            
    }
    


return S;
}

