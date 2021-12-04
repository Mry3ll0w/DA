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

template <class t>
t partition (std::vector<t> arr, size_t first, size_t last)  
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
void quickSort(std::vector<t> arr, size_t first, size_t last)  
{  
    if (first < last)  
    {  
        
        t pi = partition(arr, first, last);  
   
        quickSort(arr, first, pi - 1);  
        quickSort(arr, pi + 1, last);  
    }  
}  
  

  

int main()  
{  
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};  
      
    quickSort(arr, 0, arr.size()- 1);  
    cout << "Sorted array: \n";  
    for(auto i : arr){
        std::cout<< i<<" ";
    }  
    std::cout<<std::endl;
    return 0;  
}