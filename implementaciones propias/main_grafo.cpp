#include <iostream>
using namespace std;//Avoid using std:: ....
#include "grafo_mio.hpp"

int main(){

    initializer_list<pair<int,pair<int,int>>>l={ 
        {3,{1,2} }, { 4,{1,3} }, {0,{1,1}},
        {0,{2,2}},{7,{2,3}},{0,{3,3}}
    };
    grafo g (l,3);
    std::cout<<"--------------------------------------------------------"<<std::endl;
    cout<<KRUSKAL(g)<<std::endl;

return 0;
}