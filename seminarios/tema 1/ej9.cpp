#include <iostream>
#include <map>
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
bool voraz(std::map<double,char> ruta, double km_tanque);

int main(){

}