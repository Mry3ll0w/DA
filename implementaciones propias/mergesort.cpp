#include <iostream>
#include <list>
#include <string>
#include <vector>
/* -------------------------------------------------------------------------- */
/*                                DOCUMENTACION                               */
/* -------------------------------------------------------------------------- */
/*
Implementacion del algoritmo mergesort / ordenacion por fusion
recibira una std::list de tipo t, size_t i e size_t j, std::list<t>&B, std::list<t>& C, n = A.size()

Precondiciones==> Los elementos de la lista deben tener sobrecargado el operador <
Postcondiciones ==> Devuelve la lista de los elementos t ordenados

Tipo de Algoritmo: Divide y Vencerás(Equilibrado)


Created by @Mry3ll0w, under © GPL2.0
*/

//Funcion General de ordenacion
template <class t>
std::list<t> mergesort(const std::list<t>& A, size_t i, size_t j);

//funcion de union
template <class t>
std::list<t> merge(std::list<t>& A,size_t i, size_t k, size_t j);

//Funcion para pasar a vector la lista
template <class t>
std::vector<t> list_to_vector(const std::list<t>& l){
    std::vector<t> v;
    for (auto i: l)
    {
        v.push_back(i);
    }
    return v;
}

int main() {

return 0;
}


template <class t>
std::list<t> mergesort(const std::list<t>& A, size_t i, size_t j ) {
    size_t n = j - i + 1;

    if (n <= 3 )//n0 = 3 (dicho en clase)
    {
        A.sort();//Ordenamos la
    }
    size_t k = i - 1 = n/2;
    mergesort(A,i,k);
    mergesort(A,k+1,j);
    return merge(A,i,k,j);
    
}

template <class t>
std::list<t> merge(std::list<t>& A,size_t i, size_t k, size_t j) {
    std::list<t> w;
    size_t n = j - i + 1;
    size_t p = i;
    size_t q = k + 1;
    std::vector<t> a(A.size()),W(A.size());
    a = list_to_vector(A);


    for (size_t I = 0; I < n; I++)
    {
        if (p <= k && (q < j || a[p] <= a[q]))
        {
            w[I]=a[p];
        }
        else{
            w[I]= a[q];
            ++q;
        }
        
    }

    for (size_t I = 0; I < n; I++)
    {
        a[i-1+I]=w[I];
    }

    //pasamos el vector a lista
    std::list<t> dest(a.size());
    for(auto I: a)
        dest.push_back(I);
    return dest ;
}
