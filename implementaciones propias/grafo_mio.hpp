#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <initializer_list>
#include <bits/stdc++.h>
#include <list>
using namespace std;

/* -------------------------------------------------------------------------- */
/*                         CUANDO PRIM CUANDO KRUSKAL                         */
/* -------------------------------------------------------------------------- */
//Usamos prim cuando tengamos grafos/bosques tengamos muchos nodos, hacen lo mismo pero prim es mas optimo en este caso



//Esta clase solo recibe un grafo y no se puede modificar, es decir se crea el grafo y se acabo
class grafo{
    
    std::vector<std::vector<int>> m;
    list<pair<int,pair<int,int>>> grafo_lista;
    int vertices;
public:
    //si int min no se puede ir
    grafo(std::initializer_list<std::pair<int,std::pair<int,int>>>l, const size_t& ts);
    vector<vector<int>> matriz(){return m;}
    int n_vertices(){ return vertices; }
    list<pair<int,pair<int,int>>> grafo_forma_lista(){return grafo_lista;}
};
ostream& operator<<(ostream& os, grafo g){
    
    vector<vector<int>> m = g.matriz();
    
    for(size_t i = 0; i < m.size();++i){
        for(size_t j = 0; j < m.size();++j){
            os<<m[i][j]<<" ";
        }
        os<<"\n";
    }

return os;
}

grafo::grafo(std::initializer_list<std::pair<int,std::pair<int,int>>>l,const size_t& ts)
    : m(vector<vector<int>>(ts, vector<int>(ts))),vertices(ts),grafo_lista(l)
{
    
    for(auto i : l){//l={ { 4,{1,3} } ,{ 3,{1,2} }, {7,{2,3}}, .... }

        m[i.second.first-1][i.second.second-1]=i.first; 

    }
}


/* -------------------------------------------------------------------------- */
/*                               CLASE PARTICION                              */
/* -------------------------------------------------------------------------- */
class particion{
    list<pair<int,pair<int,int>>> s;
    
public:

    particion(pair<int, pair<int,int>> initial = {0,{0,0}}){ 

        s.push_back(pair<int, pair<int,int>>(initial.first,{initial.second.first,initial.second.second}));

    }
    
    void insert(pair<int, pair<int,int>> connection){
        s.push_back(pair<int, pair<int,int>>(connection.first,{connection.second.first,connection.second.second}));
    }
    
    bool contained(pair<int, pair<int,int>> connection){
        
        pair<int, pair<int,int>> p = connection;
        bool token = false;

        for(auto i : s){

            if(
                p.first == i.first && 
                p.second.first == i.second.first &&
                p.second.second == i.second.second
            )
            token = true;break;

        }

    return token;
    }

    list<pair<int, pair<int,int>>> part()const{return s;}

    const size_t size_partition(){return s.size();}
    
    particion& operator =(particion& p){

        s = p.s;
        return *this;
    }


    bool operator ==(particion& p){
        return s == p.s;
    }

    bool operator != (particion& p){
        return (*this == p);
    }

    particion operator+=(pair<int, pair<int,int>>p){
        s.push_back(p);
        return *this;
    }
    
    void ordena_particion(){ 
        s.sort();
    }
    
};


ostream& operator<<(ostream& os, particion p){
    
    
    for(auto i: p.part()){

        os<<"Coste: "<<i.first<<" entre "<<i.second.first<<" y "<<i.second.second<<std::endl;

    }

return os;
}

particion KRUSKAL(grafo&g ){

    particion S;//vacia con 0, {0,0}
    auto lista_t = g.grafo_forma_lista();
    lista_t.sort();
    list<pair<int, pair<int,int>>> C = lista_t;
    

    
    
    while(S.size_partition() < g.n_vertices() && !C.empty()){

        particion e1 = particion(C.front()) ;//metemos 
        C.pop_front();
        

        //Comprobamos si no esta contenido
        for (auto i : e1.part()){

            if(!S.contained(i)){
                
                //Existe camino entre ellos?
                int coste = g.matriz()[i.second.first-1][i.second.second-1];
                
                if(coste != 0){//Si esta conectado se une si no no
                   S+=pair<int, pair<int,int>>(coste,{i.second.first,i.second.second});
                }

            }
        }

    }

return S;
}
