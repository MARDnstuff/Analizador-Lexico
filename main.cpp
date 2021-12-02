#include <iostream>
#include <memory>
#include "ClaseEstado.h"
#include "ClaseTransicion.h"
#include "ClaseAFN.h"
#include "ClaseAFD.h"
#include "AnalizLexico.h"
#include "EvaluadorExp1.h"
#include <vector>

using namespace std;
Estado Edo_byID (vector<Estado> Edo,int EdoID);
void Ver_Alfabeto (vector<char> Alf);
void Ver_ConjAcept (vector<Estado> Conj);

//pruebas paso por referencia
void modifica(shared_ptr<float> prueba){
    *prueba += 1;
    return;
}

void modifica2(shared_ptr<float> prueba){
    modifica(prueba);
    *prueba +=5;

    return;
}


int main(){
/*
AFN automata = AFN();
AFN a1;
a1 = automata.AFN_Basico('+','+',0);

AFN automata2 = AFN();
AFN a2;
a2 = automata2.AFN_Basico('-','-',a1.get_Contador());

AFN automata3 = AFN();
AFN a3;
a3 = automata3.AFN_Basico('*','*',a2.get_Contador());

AFN automata4 = AFN();
AFN a4;
a4 = automata4.AFN_Basico('/','/',a3.get_Contador());

AFN automata5 = AFN();
AFN a5;
a5 = automata5.AFN_Basico('(','(',a4.get_Contador());

AFN automata6 = AFN();
AFN a6;
a6 = automata6.AFN_Basico(')',')',a5.get_Contador());

AFN automata7 = AFN();
AFN a7;
a7 = automata7.AFN_Basico('0','9',a6.get_Contador());
a7 = a7.AFN_CerrPOS();



AFN automata8 = AFN();
AFN a8;
a8 = automata8.AFN_Basico('.','.',a7.get_Contador());

a7 = a7.AFN_Conca(a8);



AFN automata9 = AFN();
AFN a9;
a9 = automata9.AFN_Basico('0','9',a7.get_Contador());
a9 = a9.AFN_CerrPOS();

a7 = a7.AFN_Conca(a9);

AFN automata10 = AFN();
AFN a10;
a10 = automata10.AFN_Basico('0','9',a7.get_Contador());
a10 = a10.AFN_CerrPOS();
a10 = a10.AFN_Union(a7);


AFN e =AFN();
e.AFN_UnionEspecial(a1,20,a10.Contador); // +
e.AFN_UnionEspecial(a2,30,a10.Contador); // -
e.AFN_UnionEspecial(a3,40,a10.Contador); // *
e.AFN_UnionEspecial(a4,50,a10.Contador); // /
e.AFN_UnionEspecial(a5,60,a10.Contador); // (
e.AFN_UnionEspecial(a6,70,a10.Contador); // )
e.AFN_UnionEspecial(a10,10,a10.Contador); // num

AFD nuevo = AFD();
nuevo = nuevo.Conv_AFNaAFD(e);
nuevo.Crea_TablaAFD();
nuevo.Guarda_TablaAFD("AFDAritmeticas");*/
AFD nuevo = AFD();
nuevo.Carga_TablaAFD("AFDAritmeticas.txt");

EvaluadorExp1 p = EvaluadorExp1("4.75+16*4/2",nuevo);
if(p.IniEval()){
    cout<<"ACEPTADA";
}else{
    cout<<"RECHAZADA";
}

/*NOTA: POR EL MOMENTO PARECE QUE TODO SALIO BIEN CON
EL DESCENSO RECURSIVO PARA EL CASO DE POSTFIJO*/
   return 0;
}


Estado Edo_byID (vector<Estado> Edo,int EdoID){
    int tam = (int) Edo.size();
    for(int i=0; i<tam;i++){
        if(Edo.at(i).get_IdEstado() == EdoID){
            return Edo.at(i);
        }//if
    }//for
    Estado e = Estado();
    e = e.Estado_null();
    return e;
}

void Ver_Alfabeto (vector<char> Alf){
    int tam = (int) Alf.size();
    cout<<"Alfabeto={";
    for(int i=0;i<tam;i++){
        cout<<Alf.at(i)<<",";
    }//for
    cout<<"}"<<endl;
    return;
}

void Ver_ConjAcept (vector<Estado> Conj){
    int tam = (int) Conj.size();
    cout<<"Estados de Aceptacion ={";
    for(int i=0;i<tam;i++){
        cout<<Conj.at(i).get_IdEstado()<<"("<<Conj.at(i).get_Token()<<"), ";
    }//for
    cout<<"}"<<endl;
    return;
}

/*
AFN automata = AFN();
AFN a1;
a1 = automata.AFN_Basico('a','c',0);

AFN automata2 = AFN();
AFN a2;
a2 = automata2.AFN_Basico('d','f',a1.get_Contador());

a1 = a1.AFN_Union(a2);
a1 = a1.AFN_CerrKleene();


AFN automata3 = AFN();
AFN a3;
a3 = automata3.AFN_Basico('g','i',a1.get_Contador());

a3 = a3.AFN_CerrPOS();

AFN automata4 = AFN();
AFN a4;
a4 = automata4.AFN_Basico('w','y',a3.get_Contador());




AFN e =AFN();
e.AFN_UnionEspecial(a1,10,a4.Contador);
e.AFN_UnionEspecial(a3,20,a4.Contador);
e.AFN_UnionEspecial(a4,30,a4.Contador);

AFD nuevo = AFD();
nuevo = nuevo.Conv_AFNaAFD(e);

Ver_Alfabeto(nuevo.Alfabeto);
vector<ConIj> temp;
temp = nuevo.get_EdoAFN();
nuevo.Crea_TablaAFD();

if(!nuevo.Guarda_TablaAFD("pruebaAFD")){
    cout<<"No se puedo guardar la tabla del AFD"<<endl;
}

AFD f1 = AFD();

f1.Carga_TablaAFD("pruebaAFD.txt");*/
