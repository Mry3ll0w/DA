#include <iostream>
#include "algoritmost2.hpp"
using namespace std;//Avoid using std:: ....

std::vector<std::vector<int>> floyd_print_k (std::vector<std::vector<int>>g, int n_vertices);

int main(){
    
    std::vector<std::vector<int>>m = {
        {0,5,0,0},
        {50,0,15,5},
        {5,0,0,15},
        {15,0,5,0}
    };

    cout<<floyd_print_k(m,m[0].size())<<std::endl;

return 0;
}

std::vector<std::vector<int>> floyd_print_k (std::vector<std::vector<int>>g, int n_vertices){

    auto sol = g;

    for(size_t i = 0; i < n_vertices; i++){
        sol[i][i]=0;
    }

    for(size_t k = 0; k < n_vertices; k++){
        
        for(size_t i = 0; i < n_vertices; i++){
            
            for(size_t j = 0; j < n_vertices; j++){

                sol[i][j]= std::min(sol[i][j],sol[i][k]+sol[k][j]);
            
            }
        
        }
        std::cout<<"-----------------------------------------------------------"<<std::endl;
        cout <<sol<<std::endl;
    }

return sol;
}
