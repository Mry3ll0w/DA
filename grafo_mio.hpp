#include <iostream>
#include<algorithm>
//declaraciones
template <class t>
class node;
template <class t>
class arista;

//Clases
template<class t>
class arista{
private:
    node<t>*n_padre;//si no apunta a nada
    node<t>*n_hijo;
    size_t peso;
public:
    arista(node<t>& n_= NULL, size_t peso_=0):n_padre(n_),peso(peso_),n_hijo(NULL){}
};

template <class t>
class node{

};