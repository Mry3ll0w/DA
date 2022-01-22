#include <iostream>
#include <list>
using namespace std;//Avoid using std:: ....

std::list<int> camionero(std::list<int> estaciones, int tanque,int destino);

int main(){
    
    list<int> estaciones={4,5,5,10,23};//  4 5 7 10  23
    
    for(auto i : camionero(estaciones,25,50)){
        cout<<i<<"---";
    }
    std::cout<<std::endl;
return 0;
}

//las estaciones se identifican con la distancia a la que esta
std::list<int> camionero(std::list<int> estaciones, int tanque,int destino){

    list<int> S,C=estaciones;
    C.sort();
    bool llegado=false;
    int recorrido=0;
    int n = tanque;

    while (!llegado && !C.empty() && recorrido < destino)
    {
        auto est = C.front();
        C.pop_front();

        if (n >= destino)//Mejor caso
        {
            S.push_back(1000);//destino llegado, salgo
            llegado=true;
        }
        else{
            
            if(n-est <= 0){
                n=tanque;
                S.push_back(est);
            }

        }

    
      n-=est;
      recorrido+=est;//metemos lo recorrido  
    }
    
return S;
}

