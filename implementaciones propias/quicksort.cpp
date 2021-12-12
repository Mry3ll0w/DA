#include <bits/stdc++.h> 
#include <algorithm>
#include <vector>
using namespace std;  

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
// Quick sort in C++

#include <iostream>
using namespace std;


// function to print the array
template <class t>
void printArray(std::vector<t>& array, int size) {
  int i;
  for (i = 0; i < size; i++)
    cout << array[i] << " ";
  cout << endl;
}

// function to rearrange array (find the partition point)
template <class t>
t partition(std::vector<t>& array, int low, int high) {
    
  // select the rightmost element as pivot
  t pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      std::swap(array[i], array[j]);
    }
  }
  
  // swap pivot with the greater element at i
  std::swap(array[i + 1], array[high]);
  
  // return the partition point
  return (i + 1);
}
template <class t>
void quickSort(std::vector<t>& array, int low, int high) {
  if (low < high) {
      
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on righ of pivot
    t pi = partition(array, low, high);

    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);

    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

// Driver code
int main() {
  std::vector<int> data = {8, 9,12,7};
  int n = data.size() ;
  
  cout << "Unsorted Array: \n";
  printArray(data, n);
  
  // perform quicksort on data
  quickSort(data, 0, n - 1);
  
  cout << "Sorted array in ascending order: \n";
  printArray(data, n);
}