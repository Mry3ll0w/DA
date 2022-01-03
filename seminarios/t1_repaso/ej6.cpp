#include <iostream>
#include "graph.hpp"


int main(){
    not_weighted_graph g;
g.insert_link(1,2);

g.insert_link(2,1);
g.insert_link(2,3);
g.insert_link(2,4);
g.insert_link(2,5);

g.insert_link(3,2);
g.insert_link(3,4);

g.insert_link(4,2);
g.insert_link(4,3);
g.insert_link(4,5);
g.insert_link(4,6);

g.insert_link(5,2);
g.insert_link(5,4);
g.insert_link(5,6);

g.insert_link(6,4);
g.insert_link(6,5);
g.insert_link(6,7);

g.insert_link(7,6);

auto aux = not_weighted_kruskal(g);
aux.print_graph();
    return 0;
}
