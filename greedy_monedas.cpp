#include <iostream>
#include <list>
//CABECERAS DE FUNCIONES y demas
struct moneda{
    size_t valor;
    size_t cantidad;
    bool operator<(const moneda b){
        return valor < b.valor;
    }
};
/*
Donde: 
    C==> es el conjunto de monedas para el cambio
    c==> es la cantidad a cambiar de monedas
*/
std::list<moneda> greedy_moneda(std::list<moneda>& C,size_t c);

int main(){

    return 0;
}

/* ------------------------- ENUNCIADO DEL PROBLEMA ------------------------- */
/*
Sea M un conjunto de monedas y c una cantidad a devolver. Por
cada tipo de moneda de valor v se dispone de un suministro de k
unidades. Se desea hallar la composición del cambio que posee el
menor número de monedas.
Una estrategia posible de selección de monedas consiste en elegir,
de las que quedan, la de mayor valor.
Esto se hace a diario en máquinas expendedoras, cajeros
automáticos, etc. Si es posible devolver el cambio con las monedas
disponibles, se actualiza el conjunto para su próximo empleo.
Conviene seleccionar todas las monedas del mismo valor de una
vez: puede tratarse M como un multiconjunto o como un conjunto
de pares
*/
/* ----------------------- FORMALIZACION DEL PROBLEMA ----------------------- */
/*
    Conjunto inicial: Las cantidad de monedas (numero y valor)
    Función Solución: Comprueba si la cantidad de monedas especificada esta correcta
    Funcion de seleccion: Devuelve la moneda de mayor valor posible junto con su cantidad de monedas
    Funcion de factibilidad:¿Es posible devolver las monedas sin exceder al cambio?
    Funcion Objetivo: EL valor total de los objetos devueltos
    Objetivo: minimizar la cantidad de monedas
*/

//funcion de seleccion de monedas
moneda& funcion_seleccion(std::list<moneda>& C){
    moneda m;//m tiene el valor minimo de la moneda (-inf ~= 0 ) ya que el valor minimo de una moneda es 1 cts
    for (auto i:C)
    {
        if (m.valor<i.valor)
        {
            m.valor = i.valor;
            m.cantidad =i.cantidad;
        }
        
    }
    return m;
}

//algoritmo devorador
std::list<moneda> greedy_moneda(std::list<moneda>& C, size_t c){
   //C <- C de entrada
   std::list<moneda>S; //conjunto solucion S<-0
   //creamos una variable para almacenar la moneda candidata
   moneda temp_moneda;
   //para mejorar el algoritmo ordenamos

   while (!C.empty()&& c!=0)//mientras que existan monedas en el conjunto o se cambie todo
   {
       temp_moneda = funcion_seleccion(C);
       //PREGUNTAR SALGUERO 
   }
    
}
