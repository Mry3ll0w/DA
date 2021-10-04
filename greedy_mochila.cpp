#include <iostream>
#include <vector>
/* ENUNCIADO
    Dado un conjunto de objetos, cada uno con un valor v y un peso p.
    Una mochila de capacidad c(que limita el peso total de la mochila).
    Se desa hallar la composición de la mochila que maximiza el valor de
    la carga.
    En su version continua, los objetos pueden fraccionarse y el problema
    puede resolverse optimamente con un algoritmo devorador.
    Tiene 3 posibles estrategias de selección de objetos:
        a) orden decreciente en valor
        b) orden orden creciente de peso
        c) En orden decreciente de relacion valor/peso <- Mayor cantidad de optimizacion
    DATOS DE EJEMPLO:
        Objetos) 
        10 kg agua con un coste total de 5 €        ==> 0.5 €/kg
        3 kg de gasoil con un coste total de 3€     ==> 1 €/kg
        4 kg de aceite con un coste total de 5€     ==> 1.25€/kg
        Mochila) Capacidad de 4kg 
*/
/* ----------------------- FORMALIZACION DEL PROBLEMA -----------------------
    Conjunto inicial: Los objetos dados
    Función Solución: Comprueba si la mochila esta completa
    Funcion de seleccion: Devuelve el objeto con mayor ratio valor peso
    Funcion Objetivo: EL valor total de los objetos devueltos
    Objetivo: maximizar
*/
struct objeto{
    double valor;
    double peso;
};
struct mochila{
    double capacidad;
};
std::vector<objeto>& greedy_mochila(std::vector<objeto>& C);
int main(){
    //DATOS DADOS DE INICIO
    std::vector<objeto> obs{{10,0.5},{3,1},{1,1.25}};// en vez de conjunto vector
    mochila m; m.capacidad = 4;
    // llamada al procedimiento greedy
    

    return 0;
}