#include <iostream>
#include<algorithm>
#include<string>
#include<vector>
//declaraciones
template <class t>
class node;
template <class t>
class arista;

//Clases
template<class t>
class arista{
private:
    node<t>*n1;// nodo lado 1 
    node<t>*n2;// nodo lado 2
    size_t peso;
public:
    arista(node<t>& n_= NULL, size_t peso_=0):n1(n_),peso(peso_),n2(NULL){}
    void asociar_n1(const node<t>& n_p){
        n1=n_p;
    }
    void asociar_n2(const node<t>& n_p){
        n2 = n_p;
    }
    void asignar_peso(size_t p){peso=p;}
    ~arista(){
        delete n1;
        delete n2;
    }
};

template <class t>
class node{
private:
    std::vector<arista<t>> a;
    t tag; //Identificador del nodo
    const size_t buscar_tag(const node<t>& n, t tag);
public:
    node(std::string id):tag(id){
        //inicializar arista
        arista<t> a(this);
        a.insert(a.end(),a);
    }
    void insertar_relacion(const node<t>& n2,size_t peso);
};

template <class t>
const size_t node<t>::buscar_tag(const node<t>& n, t tag){
    bool token=false;
    size_t i=0;
    for(; i<n.a.size() && !token; ++i){
        if (n[i].tag == tag )
        {
            token = true;
        }
    }
    return i; 
}

template <class t>
void node<t>::insertar_relacion(const node<t>& n2, size_t peso){
    //buscamos donde esta en que arista esta el nodo
    size_t pos = buscar_tag(this,this->tag);
    this->a[pos].asociar_n2(n2);
    this->a[pos].asignar_peso(peso);
}

//clase grafo
template <class t>
class graph{
private:
    std::vector<node<t>> nodes;//Un grafo esta formado por x nodos (a su vez los nodos tienen aristas)
public:
    graph();//ya que existe un grafo vacio
    void insertar_nodo(const node<t>& n);//comprobar que no existe un nodo en el grafo
    const std::vector<node<t>> nodes_getter(){return nodes;}
};