#include <iostream>

#include<list>
class not_weighted_graph{
private:
    std::list<std::pair<int, int>>g;//el grafo queda representado como una lista de uniones (no ponderado)
public:
    
    not_weighted_graph(const int& a = 0, const int& b = 0){//Ctor predeterminado para poder crear un grafo vacio
       if(a!=0 || b!=0){
            g.push_back(std::make_pair(a,b));
       }
    }
    
    bool empty(){return g.size()==0;}//Si el size es 0 entonces esta vacio
    
    //Receives a as the main link and b as the one who is hanging (a ---- b)
    void insert_link(const int& a, const int& b){
        g.push_back(std::make_pair(a,b));//is inserted anyway (can't have any duplicated pair of int)
    }

    void show_links(const int& a){

        for(auto i: g){
            if(i.first == a )
                std::cout<< i.first << "----"<<i.second<<std::endl;
        }

    }

    //Erases the link composed of a and b
    void erase_link(const int& a, const int& b){
        for(auto i=g.begin(); i!=g.end(); i++){
            if(i->first == a && i->second == b)
                g.erase(i);break;
        }
    }

    //Checks if a link is in the graph
    bool is_link(const int&a, const int& b){
        bool found =false;
        for(auto i=g.begin(); i!=g.end() && !found; i++){
            if(i->first == a && i->second == b)
                found=true;
        }
        return found;
    }

    //List of all node tags in the graph
    std::list<int> nodes(){
        std::list<int> l;size_t cont=0;
        for(auto i: g){
            cont=0;
            for(auto j: l){
                
                if(j==i.first)   
                    ++cont;
            
            }
            if(cont<2)
                l.push_back(i.first);//if not duplicated inser in list

        }
    return l;
    }

    void print_graph(){
        for(auto i: g){

            std::cout << i.first <<"----"<<i.second<<std::endl;
        }
    }

    std::list<std::pair<int,int>> get_graph(){return g;}

};

//To represent of a weighted graph
class graph{
private:
    std::list<std::pair<int,std::pair<int, int>>> g;//el grafo queda representado como una lista de uniones (no ponderado)
public:
    
    void print_graph(){
        for(auto i: g){

            std::cout << i.second.first <<"----"<<i.second.second<<"Cost= "<<i.first<<std::endl;
        }
    }

    graph(const int& a = 0, const int& b = 0, const int&c=0){//Ctor predeterminado para poder crear un grafo vacio
        if(a!=0 || b!=0 || c!=0)
            g.push_back(std::make_pair(c,std::make_pair(a,b)));
    }
    
    bool empty(){return g.size()==0;}//Si el size es 0 entonces esta vacio
    
    //Receives a as the main link and b as the one who is hanging (a ---- b)
    void insert_link(const int& a, const int& b,const int& c){
       g.push_back(std::make_pair(c,std::make_pair(a,b)));//is inserted anyway (can't have any duplicated pair of int)
    }

    //Show linked nodes with a 
    void show_links(const int& a){

        for(auto i: g){
            if(i.second.first == a )
                std::cout<< i.second.first << "----"<<i.second.second<<std::endl;
        }

    }

    //Erases the link composed of a and b
    void erase_link(const int& a, const int& b){
        for(auto i=g.begin(); i!=g.end(); i++){
            if(i->second.first == a && i->second.second == b)
                g.erase(i);break;
        }
    }

    //Checks if a link is in the graph
    bool is_link(const int&a, const int& b){
        bool found =false;
        for(auto i=g.begin(); i!=g.end() && !found; i++){
            if(i->second.first == a && i->second.second == b)
                found=true;
        }
        return found;
    }

    //List all the nodes in the graph
    std::list<int> nodes(){
        std::list<int> l;size_t cont=0;
        for(auto i: g){
            cont=0;
            for(auto j: l){
                
                if(j==i.second.first)   
                    ++cont;
            
            }
            if(cont<2)
                l.push_back(i.second.first);//if not duplicated inser in list

        }
    return l;
    }

    std::list<std::pair<int,std::pair<int, int>>> get_graph(){return g;}
    

};



/* -------------------------------------------------------------------------- */
/*                            ALGORITMO DE KRUSKAL                            */
/* -------------------------------------------------------------------------- */

bool is_expansion_tree(not_weighted_graph& g1, not_weighted_graph& source_graph){
    
    //If both list are equal it is indeed an expansion tree
    return g1.nodes()==source_graph.nodes();

}

not_weighted_graph not_weighted_kruskal(not_weighted_graph g){
    
    not_weighted_graph S;
    

   


return S;
}