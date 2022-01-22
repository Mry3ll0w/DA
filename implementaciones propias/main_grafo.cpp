#include <iostream>
using namespace std;//Avoid using std:: ....
#include "grafo_mio.hpp"

int main(){

    initializer_list<pair<int,pair<int,int>>>l={ 
        {3,{1,2} }, { 4,{1,3} }, {0,{1,1}},
        {0,{2,2}},{7,{2,3}},{0,{3,3}}
    };

    initializer_list<pair<int,pair<int,int>>>l2={
        {0,{1,1}},{0,{2,2}},{0,{3,3}},{0,{4,4}},{0,{5,5}},{0,{6,6}},{0,{7,7}},
        {1,{1,2}},{8,{2,5}},{8,{2,4}},{8,{2,3}},
        {7,{3,4}},{6,{4,5}},{9,{4,6}},
        {9,{5,6}},{4,{6,7}}

    };
    grafo g (l2,7);
    std::cout<<"--------------------------------------------------------"<<std::endl;
    cout<<KRUSKAL(g)<<std::endl;

return 0;
}