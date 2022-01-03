#include <iostream>
#include <vector>
#include <algorithm> //std::Swap
#include <random> //random_device
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
    2)size_t low : By default 0 (the first position of the vector to be sorted)
    3)size_t high : Last position of the vector to be sorted (by default vector.size() - 1 )

Created by @Mry3ll0w, under © GPL2.0.
*/ 
template <class t>
t partition(std::vector<t>& array, int low, int high) {
    
  t pivot = array[high];
  
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;  
      std::swap(array[i], array[j]);
    }
  }
  
  std::swap(array[i + 1], array[high]);
  
  return (i + 1);
}

template <class t>
void quickSort(std::vector<t>& array, int low, int high) {
  if (low < high) {
      
    t pi = partition(array, low, high);

    quickSort(array, low, pi - 1);

    quickSort(array, pi + 1, high);
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
    std::cout<<prueba_vec_dinamico()<<std::endl;
    return 0;
}

bool prueba_vec1(){
    
    bool ordenado = true; 
    std::vector<int>v={9,7};
    std::vector<int>v2={7,9};//Contiene el vector final ordenado

    
    //mergeSort(v,0,v.size()-1);
    quickSort(v,0,v.size()-1);
    for(size_t i=0;i<v.size();i++){
        if(v[i]!= v2[i]){
            ordenado= false;
        }
    }
    
    return ordenado;

}

bool prueba_vec_dinamico(){
    std::vector<int>v,v_sorted;
    bool ordered = true;
    size_t tam = 10;//Empezamos con vectores de tamaño

    while (tam < 1000 && ordered)
    {   
        //1)inicializamos el vector con los n primeros elementos
        v= std::vector<int>(tam);
        for (size_t i = 0; i < tam; i++)
        {
            v[i]=i+1;
        }
        v_sorted = v; // En ese momento v ya esta ordenado [1...tam]
        
        //2)Hacemos un shuffle de v
        std::shuffle(v.begin(), v.end(), std::random_device());
        //3)Llamaremos al sort que queramos y comprobamos  si falla o no
        //quickSort(v,0,v.size()-1);
        mergeSort(v,0,v.size()-1);

        //4)Comprobamos que los elementos esten ordenados
        for(size_t i = 0; i < tam && ordered; i++){
            if(v[i]!=v_sorted[i]){
                ordered = false;
            }
        }


        //Incrementamos tam para el siguiente vector
        tam++;
    }
    
return ordered;
}