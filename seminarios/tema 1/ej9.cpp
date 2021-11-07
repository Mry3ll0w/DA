#include <iostream>
#include <map>
#include <list>
/* -------------------------------------------------------------------------- */
/*                                  ENUNCIADO                                 */
/* -------------------------------------------------------------------------- */
/*
Un camión ha de cubrir una ruta en la que existen m estaciones de servicio e1,...,em. El
camionero desea parar en el mínimo número posible de estaciones de servicio, teniendo en
cuenta que llena el depósito cada vez que para, lo que le permite recorrer n kilómetros. El
camionero parte con el depósito lleno y conoce las distancias entre las distintas estaciones,
su lugar de origen y su destino como se muestra en la figura.
Parametros de Entrada: 
    map[double coste, char id_Estacion] ( Se sobre entiende que la ultima posicion del map)
    double km_tanque ==> cuanto km recorre el coche con el tanque lleno
*/
struct ruta {
    double distancia;
    char tag;
    ruta(const double& d=0, const char& c=' '):distancia(d), tag(c){}
};
bool voraz(std::list<ruta> &rute, double km_tanque,std::list<ruta>&dest);

int main(){
    std::list<ruta> c={{3.5,'a'},{7.5,'b'},{9.5,'c'},{13.5,'d'}};
    std::list<ruta> s;
    std::cout<<voraz(c,12,s)<<std::endl;
    for (auto i:s)
    {
        std::cout<<i.tag<<", ";
    }
    std::cout <<std::endl;
return 0;
}
//NO existe una funcion de seleccion
bool voraz(std::list<ruta>& rute, double km_tanque,std::list<ruta>&dest){
    bool token=true;
    std::list<ruta>C=rute;
    std::list<ruta>S;
    ruta p;
    while (C.size() > 0 && token == false)
    {
        p = C.front();
        C.pop_front();//saca la delantera

        if ((km_tanque-p.distancia)>0)//si llega al destino entonces "reposta" y sigue al siguiente destino
        {
            S.push_back(p);
        }
        else{//no llega al destino y se para ==> token a false y lista actualizada
            token = false;
        }
    }
    dest = S;
    return token;
}