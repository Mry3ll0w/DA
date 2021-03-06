#include <iostream>
#include <list>
#include <string>
#include <vector>
/* -------------------------------------------------------------------------- */
/*                                DOCUMENTACION                               */
/* -------------------------------------------------------------------------- */
/*
Implementacion del algoritmo mergesort / ordenacion por fusion
recibira una std::vector<t> &arr, size_t l, size_t m, size_t r

Precondiciones==> Los elementos de la lista deben tener sobrecargado el operador <
Postcondiciones ==> Devuelve la lista de los elementos t ordenados

Tipo de Algoritmo: Divide y Vencerás(Equilibrado)

El parámetro i representa la posición a partir de la cual pretende ordenarse el vector v. 
De forma análoga, el parámetro j representa posición del vector v hasta donde pretende 
realizarse la ordenación. El parámetro k representa la posición intermedia que divide 
el vector original en los dos subvectores que van a ser fusionados.

Created by @Mry3ll0w, under © GPL2.0
*/
template <class t>
void merge(std::vector<t> &arr, size_t l, size_t m, size_t r)
{
    size_t n1 = m - l + 1;
    size_t n2 = r - m;
        
    std::vector<t>L(n1),R(n2);
   
    for (int i = 0; i < n1; i++){//copia la parte izquierda al centro
        L[i] = arr[l + i];
    }
        
    for (int j = 0; j < n2; j++){//copia la parte derecha al centro
         R[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
  
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
   
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

}
 
template <class t>
void mergeSort(std::vector<t> &arr,size_t l,size_t r){
    if(l>=r){
        return;
    }
    size_t m = (l+r-1)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}
bool operator < (const std::string &a, const std::string &b){
        return a.size()<b.size();
}

int main() {
    

}