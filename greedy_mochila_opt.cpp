#include <iostream>
#include <vector>
#include <list>
/* ENUNCIADO V2
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
  ----------------------- MEJORA CON RESPECTO AL OTRO ----------------------
  Para reducir su coste de implentacion con respecto al tiempo de ejecución implementaremos un preorden
  mediante una funcion de ordenacion para reducir de O(n^2) a O(n* log n) la cual es mejor. 
*/
struct objeto{
    double valor;
    double peso;
    bool operator < (const objeto& b){
        return (valor/peso)<(b.valor/b.peso);
    }
};
struct mochila{
    double capacidad;
};
std::vector<objeto>& greedy_mochila(mochila& m,std::vector<objeto>& C);
int main(){
    //DATOS DADOS DE INICIO
    std::vector<objeto> obs{{10,0.5},{3,1},{1,1.25}};// en vez de conjunto vector
    mochila m; m.capacidad = 4;
    // llamada al procedimiento greedy
    std::vector<objeto> conjunto_solucion;
    conjunto_solucion = greedy_mochila(m,obs);

    return 0;
}
/*
mochila : O × c → S
C ← O
S ← ∅
mientras c 6= 0 ∧ C 6= ∅
    hv, pi ← selecciona-objeto(C)
    C ← C − {hv, pi}
    si p ≤ c
        S ← S ∪ {hv, pi}
        c ← c − p
    si no
        S ← S ∪ {hv · c/p, ci}
    c ← 0
*/

//Funcion de ordenacion para mejora temporal
std::vector<objeto> funcion_ordenacion(std::vector<objeto>& c){
    std::list<objeto> temp_list;
    std::vector<objeto> temp_vector;
    objeto temp_obj;
    for(auto it : c){
        temp_obj.valor = it.valor;
        temp_obj.peso  = it.peso;

        temp_list.insert(temp_list.end(),temp_obj);
    }
    temp_list.sort();//ORDENA LOS ELEMENTOS DE LA LISTA SEGUN LA SOBRECARGA REALIZADA con anterioridad
    for (auto i: temp_list)
    {
        temp_vector.insert(temp_vector.end(),i);
    }
    return temp_vector;
} 

//Funcion de seleccion de objeto candidato perteneciente al conjunto
objeto seleccion_objeto(std::vector<objeto>& C){
    double r= -1; // Lo igualamos a -infinito para iterar desde el primer elemento
    objeto t;
    for (auto i : C)//Recorremos el conjunto SIN ELIMINAR ya que se hace de forma externa (no competencia de esta funcion)
    {
        if ( (i.valor/i.peso) > r)//¿Cual tiene mejor ratio valor/peso??
        {
            r = i.valor/i.peso;
            // {v,p} <- {a, b}
            t.valor = i.valor;
            t.peso = i.peso;
        }
    }
    return t;
}

//Funcion de poda de conjunto (ya que no tenemos la union de los mismos implementado)
void podar_conjunto(std::vector<objeto>& v,const objeto& o){
    size_t it=0;
    while (it<v.size()||(v[it].peso==o.peso && v[it].valor==o.valor))
    {
        ++it;
    }
    if (v[it].peso==o.peso&& v[it].valor==o.valor)
    {
        v.erase(v.begin()+it);
    }
    
}

//DEVORADOR DE MOCHILA
std::vector<objeto>& greedy_mochila(mochila &m ,std::vector<objeto>& C){
    objeto temp_obj;
    C = funcion_ordenacion(C);//MEJORA con preordenacion para conseguir orden O(n* log n)
    std::vector<objeto>S;
    while (!C.empty()&& m.capacidad!=0 )//mientras el conjunto no este vacio
    {
        temp_obj = seleccion_objeto(C);//Obtenemos el "mejor candidato"
        std::cout<<"mejor objeto (peso)= "<< temp_obj.peso<<std::endl;
        podar_conjunto(C,temp_obj);// C <- C - {v.p}
        
        //ESPECIFICA DEL PROBLEMA

        if (temp_obj.peso<= m.capacidad)//Si cabe entonces
        {
            S.insert(S.end(),temp_obj);// S <- S U {v, p}
            m.capacidad-=temp_obj.peso;//Actualizamos la capacidad de la mochila 
        }
        else{//Si no cabe entonces
            temp_obj.valor=(temp_obj.peso*m.capacidad)/temp_obj.peso;
            //cuanto valor en funcion del peso disponible nos podemos llevar del objeto
            temp_obj.peso=m.capacidad;
            S.insert(S.end(), temp_obj);//metemos el objeto en la mochila
            m.capacidad=0;//Hemos agotado la maxima capacidad de la mochila 
        }
    }
    
}