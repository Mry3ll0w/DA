#include <iostream>
#include <vector>

/* -------------------------------------------------------------------------- */
/*                           ALGORTIMO DE ORDENACION                          */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                          ALGORITMOS DE ORDENACION                          */
/* -------------------------------------------------------------------------- */


/* ----------------------- QUICKSORT/ORDENACION RAPIDA ---------------------- */

/* -------------------------------------------------------------------------- */
/*                             DOCUMENTATION_BLOCK                            */
/* -------------------------------------------------------------------------- */
/*
Preconditions: 
    1)An initilized vector of t elements
    2)size_t first : By default 0 (the first position of the vector to be sorted)
    3)size_t last : Last position of the vector to be sorted (by default vector.size() - 1 )

Created by @Mry3ll0w, under © GPL2.0.
*/ 

template <class t>
t partition (std::vector<t> &arr, size_t first, size_t last)  
{  
    t pivot = arr[last];  
    size_t i = (first - 1);  
  
    for (int j = first; j <= last - 1; j++)  
    {  
     
        if (arr[j] < pivot)  
        {  
            i++;  
    
            std::swap(arr[i], arr[j]);  
        }  
    }  
    std::swap(arr[i + 1], arr[last]);  
    return (i + 1);  
}  

/*
RECURSIVE method to call partition
*/
template <class t>
void quickSort(std::vector<t>& arr, size_t first, size_t last)  
{  
    if (first < last)  
    {  
        
        t pi = partition(arr, first, last);  
   
        quickSort(arr, first, pi - 1);  
        quickSort(arr, pi + 1, last);  
    }  
}  


/* -------------------- MERGESORT / ORDENACION POR FUSION ------------------- */
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

bool prueba_vec1();
bool prueba_vec_dinamico();

int main(){
    //std::shuffle(container.begin(), container.end(), std::random_device());
    std::cout<<prueba_vec1()<<std::endl;
    return 0;
}

bool prueba_vec1(){
    
    bool ordenado = true; 
    std::vector<int>v={9,7,1,12};
    std::vector<int>v2={1,7,9,12};//Contiene el vector final ordenado

    
    //mergeSort(v,0,v.size()-1);
    quickSort(v,0,v.size()-1);
    std::cout<<"termino quickSort"<<std::endl;
    for (auto i:v){
        std::cout<<i<<std::endl;
    }
    for(size_t i=0;i<v.size();i++){
        if(v[i]!= v2[i]){
            ordenado= false;
        }
    }
    
    return ordenado;

}