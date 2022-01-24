#include <iostream>
#include "algoritmost2.hpp"

using namespace std;//Avoid using std:: ....

int main(){
    std::vector<std::vector<int> > g = {
        {1,2,4},//desde nodo 1 cuanto vale el resto
        {3,1,1},
        {5,2,4}
    };
    //apartado A)
    //Este algoritmo es simplemente aplicar el algoritmo de Floyd a la matriz que nos dan
    auto g2 = floyd(g,3);

    for(size_t i = 0; i < 3; i++){
        
        for (size_t j = 0; j < 3; j++)
        {
            cout<<g2[i][j]<<" ";    
        }
        cout<<endl;
    }

    //Apartado b) obtener una matriz de adyancencia

return 0;
}

