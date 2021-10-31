#include <iostream>
#include <string>
#include <list>

/*
Un fontanero dispone de varios segmentos de tubo de distintas longitudes. 
Diseñe un algoritmo que, siguiendo una estrategia devoradora, minimice el número de uniones necesarias
para construir una única tubería de longitud l. 
El fontanero puede realizar los cortes en los tubos que considere oportunos. 
Analice la complejidad del algoritmo.
*/



std::list<int> voraz(std::list<int>C , int longitud);

int main(){
    std::list<int> c = {2,4,5,7,9};
    std::list<int> s;
    s = voraz(c,18);

    for(auto i : s){
        std::cout << i <<", ";
    }
    std::cout<<std::endl;
    return 0;
}

//La lista se recibe ordenada de menor a mayor por tanto el mayor sera el que se encuetra a la derecha
int funcion_seleccion(std::list<int> c){
    return c.back();
}

std::list<int> podar(std::list<int>c){
    std::list<int> res;
    for (auto i : c)
    {
        if ( i != c.back())
        {
            res.push_back(i);
        } 
    }
    return res;
}

std::list<int> voraz(const std::list<int>c , int longitud){
    std::list<int> S;
    std::list<int> C= c;//copiamos en C la lista de candidatos de entrada
    C.sort();//para reducir el orden de N^2 a n·log n
    int p=0;
    while(C.size()>0 && longitud > 0){
        p = funcion_seleccion(C);
        //podamos la lista desde el final
        C=podar(C);
        if (p <= longitud)
        {
            longitud-= p;
            S.push_back(p);
        }
        else{
            longitud = 0;
        }
        
    }

    return S;
}


