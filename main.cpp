#include <iostream>
#include "ClaseEstado.h"
#include "ClaseTransicion.h"
#include "ClaseAFN.h"
#include <vector>
using namespace std;




int main(){

AFN automata = AFN();
AFN a1;
a1 = automata.AFN_Basico('a','c',0);

AFN automata2 = AFN();
AFN a2;
a2 = automata2.AFN_Basico('d','f',a1.get_Contador());

a1 = a1.AFN_Union(a2);


AFN automata3 = AFN();
AFN a3;
a3 = automata3.AFN_Basico('g','i',a1.get_Contador());


a1=a1.AFN_Conca(a3);

a1 = a1.AFN_CerrKleene();

a1= a1.AFN_Opcional();

automata.Mx_Adyacencia(a1);


    return 0;
}
