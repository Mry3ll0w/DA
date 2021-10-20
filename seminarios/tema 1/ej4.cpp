#include <iostream>
#include <list>
#include <string>
class programa{
private:
    double peso;
    std::string tag;
public:
    programa(double p ,std::string t):peso(p),tag(t){}
    programa(const programa& p){
        peso = p.peso;
        tag = p.tag;
    }
    const double peso_get() const {return peso;}
    const std::string tag_get() const {return tag;}
    bool operator <(const programa& p) const{
        return peso < p.peso_get(); 
    }
};
bool operator==(const programa&a, const programa& b){
    return a.peso_get() == b.peso_get();
}

//funcion de seleccion
programa funcion_seleccion(std::list<programa>& c){
    return c.front();
}

std::list<programa> greedy_ej4(const std::list<programa>& c,double capacidad){
    //variables
    std::list<programa> C = c;
    std::list<programa> S;
    //algoritmo
    C.sort();//organizamos la entrada
    
    while (C.size() > 0 && capacidad > 0)
    {
        programa p = funcion_seleccion(C);
        C.erase(C.begin());//eliminamos el programa sacado
    
        if (capacidad - p.peso_get() > 0)//para maximizar el numero de programas
        {
            S.insert(S.end(),p);
            capacidad -= p.peso_get();
        }
        else{
            capacidad = 0;
        }
    }
return S;
}

//Optimizar el uso del disco ==> Espacio sobrante sea el menor posible, coger los programas mas grandes
std::list<programa> greedy_ej4_apartado_b(const std::list<programa>& c,double capacidad){
    //variables
    std::list<programa> C = c;
    std::list<programa> S;
    //algoritmo
    C.sort();//organizamos la entrada

    while (C.size() > 0 && capacidad > 0)
    {
        programa p = funcion_seleccion(C);
        C.erase(C.begin());//eliminamos el programa sacado
        if (p.peso_get() < capacidad)//para maximizar el numero de programas
        {
            
            S.insert(S.end(),p);
            capacidad -= p.peso_get();
        }
        else{
            capacidad = 0;
        }
    }
return S;
}

int main(){
    std::list<programa>lista,fin;
    lista.insert(lista.end(),programa(2,"WinRar"));
    lista.insert(lista.end(),programa(1.6,"Daemon Tools"));
    lista.insert(lista.end(),programa(1.5,"Steam"));
    lista.insert(lista.end(),programa(32,"League of Legends"));
    lista.insert(lista.end(),programa(7.6,"VsCode"));
    lista.sort();
    
    
    fin = greedy_ej4_apartado_b(lista,27.1);
    //algoritmo 2 
    for (auto i:fin){
        std::cout<<i.tag_get()<<": "<<i.peso_get()<<std::endl;
    }
    
    return 0;
}