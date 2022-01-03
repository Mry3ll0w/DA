#include <iostream>
#include <list>

typedef struct objeto{
    int value;
    int peso;
    float ratio;
    objeto(const int v, const int p):ratio(v/p),value(v),peso(p) {}
    bool operator<(const objeto& o){
        return ratio < o.ratio;
    }
};

std::list<objeto> devorador(std::list<objeto> c,int peso){

    std::list<objeto> S;
    c.sort();

    while (!c.empty() && peso > 0)
    {
        objeto p = c.back();
        c.pop_back();

        if( peso - p.peso > 0){
            S.push_back(p);
            peso -=p.peso;
        }

    }
    

return S;
}


int main(){
    
    return 0;
}