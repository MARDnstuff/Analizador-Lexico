#include <iostream>
#include <memory>
#include "ClaseEstado.h"
#include "ClaseTransicion.h"
#include "ClaseAFN.h"
#include "ClaseAFD.h"
#include "AnalizLexico.h"
#include "EvaluadorExp1.h"
#include "ER_AFN.h"
#include "DescRecGram_Gram.h"
#include "AnalizadorLL1.h"
#include <vector>
#include <list>

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

    AnalizadorLL1 e = AnalizadorLL1("E -> T Ep; Ep -> mas T Ep| menos T Ep |epsilon; T -> F Tp; Tp -> prod F Tp | div F Tp | epsilon; F -> parI E parD | num;");
    e.CrearTablaLL1();
    //cout<<e.column<<endl;

    for(int i=0; i<e.row; i++){
        for(int j=0; j<e.column; j++){
          cout<<e.TablaLL1[i][j]<<" ";
        }//for
        cout<<endl;
    }//for
    //incializar el tamaño de Vt3
    e.Vt3 = new int[e.column];
    int token;
    for(int i=0; i<e.column; i++){
        cout<<"Introduce el Token para:"<<e.Vt[i].Simbolo<<" -->";
        cin>>token;
        e.Vt3[i] = token;
        cout<<e.Vt3[i]<<endl;
    }

    /*
        e.AFN_UnionEspecial(a1,20,a10.Contador); // +
        e.AFN_UnionEspecial(a2,30,a10.Contador); // -
        e.AFN_UnionEspecial(a3,40,a10.Contador); // *
        e.AFN_UnionEspecial(a4,50,a10.Contador); // /
        e.AFN_UnionEspecial(a5,60,a10.Contador); // (
        e.AFN_UnionEspecial(a6,70,a10.Contador); // )
        e.AFN_UnionEspecial(a10,10,a10.Contador); // num
    */
    e.SetLexico("AFDAritmeticas.txt");
    e.LexGram.SetSigma("5+5");

    cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;
    cout<<e.LexGram.yylex()<<" --> "<<e.LexGram.Lexema<<endl;

    if(e.AnalizSintacLL1("2.57*(12+16-8)/13-17)")){ //<-- Es el caso de erro resolverlo YYAAA
        cout<<"cadena correcta"<<endl;
    }else{
        cout<<"cadena incorrecta"<<endl;
    }
    //  REVISAR ANALISIS LL1

   return 0;
}

//E -> T Ep; Ep -> mas T Ep| menos T Ep |epsilon; T -> F Tp; Tp -> prod F Tp | div F Tp | epsilon; F -> parI E parD | num;
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
//Pruebas
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

//Aritmeticas
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


// Expresion Regular a AFN
    // OR
    /*AFN automata = AFN();
    AFN a1;
    a1 = automata.AFN_Basico('|','|',0);
    // CONC
    AFN automata2 = AFN();
    AFN a2;
    a2 = automata2.AFN_Basico('&','&',a1.Contador);
    // CERR_POS
    AFN automata3 = AFN();
    AFN a3;
    a3 = automata3.AFN_Basico('+','+',a2.Contador);
    // CERR_KLE
    AFN automata4 = AFN();
    AFN a4;
    a4 = automata.AFN_Basico('*','*',a3.Contador);
    //OPC
    AFN automata5 = AFN();
    AFN a5;
    a5 = automata5.AFN_Basico('?','?',a4.Contador);
    //PAR_I
    AFN automata6 = AFN();
    AFN a6;
    a6 = automata6.AFN_Basico('(','(',a5.Contador);
    // PAR_D
    AFN automata7 = AFN();
    AFN a7;
    a7 = automata7.AFN_Basico(')',')',a6.Contador);
    //CORCH_I
    AFN automata8 = AFN();
    AFN a8;
    a8 = automata8.AFN_Basico('[','[',a7.Contador);
    //CORCH_D
    AFN automata9 = AFN();
    AFN a9;
    a9 = automata9.AFN_Basico(']',']',a8.Contador);
    //GUION
    AFN automata10 = AFN();
    AFN a10;
    a10 = automata10.AFN_Basico('-','-',a9.Contador);
    //SIMBOLO
    //--> [a - z]
    AFN automata11 = AFN();
    AFN a11;
    a11 = automata11.AFN_Basico('a','z',a10.Contador);

    //--> [A - Z]
    AFN automata12 = AFN();
    AFN a12;
    a12 = automata12.AFN_Basico('A','Z',a11.Contador);

    // --> [0 - 9]
    AFN automata13 = AFN();
    AFN a13;
    a13 = automata13.AFN_Basico('0','9',a12.Contador);

    // --> [A - z] | [a - z] | [0 - 9]
    a13 = a13.AFN_Union(a11);
    a13 = a13.AFN_Union(a12);

    // --> |
    AFN automata14 = AFN();
    AFN a14;
    a14 = automata14.AFN_Basico('|','|',a13.Contador);

    // --> &
    AFN automata15 = AFN();
    AFN a15;
    a15 = automata15.AFN_Basico('&','&',a14.Contador);
     // --> +
    AFN automata16 = AFN();
    AFN a16;
    a16 = automata16.AFN_Basico('+','+',a15.Contador);
    // --> *
    AFN automata17 = AFN();
    AFN a17;
    a17 = automata17.AFN_Basico('*','*',a16.Contador);
     // --> ?
    AFN automata18 = AFN();
    AFN a18;
    a18 = automata18.AFN_Basico('?','?',a17.Contador);
     // --> (
    AFN automata19 = AFN();
    AFN a19;
    a19 = automata19.AFN_Basico('(','(',a18.Contador);
     // --> )
    AFN automata20 = AFN();
    AFN a20;
    a20 = automata20.AFN_Basico(')',')',a19.Contador);
     // --> [
    AFN automata21 = AFN();
    AFN a21;
    a21 = automata21.AFN_Basico('[','[',a20.Contador);
     // --> ]
    AFN automata22 = AFN();
    AFN a22;
    a22 = automata22.AFN_Basico(']',']',a21.Contador);
     // --> -
    AFN automata23 = AFN();
    AFN a23;
    a23 = automata23.AFN_Basico('-','-',a22.Contador);

    // --> '\'
    AFN automata24 = AFN();
    AFN a24;
    a24 = automata24.AFN_Basico('\\','\\',a23.Contador);


    // --> Concatenacion de simbolos
    a24 = a24.AFN_Union(a14);
    a24 = a24.AFN_Union(a15);
    a24 = a24.AFN_Union(a16);
    a24 = a24.AFN_Union(a17);
    a24 = a24.AFN_Union(a18);
    a24 = a24.AFN_Union(a19);
    a24 = a24.AFN_Union(a20);
    a24 = a24.AFN_Union(a21);
    a24 = a24.AFN_Union(a22);
    a24 = a24.AFN_Union(a23);

        // --> '\'
    AFN automata25 = AFN();
    AFN a25;
    a25 = automata25.AFN_Basico('\\','\\',a24.Contador);
    a25 = a25.AFN_Conca(a24);

    // Completo
    a13 = a13.AFN_Union(a25);
    // Diagonales invertidas
   AFN automata26 = AFN();
    AFN a26;
    a26 = automata26.AFN_Basico('\\','\\',a13.Contador);
    //Union especial
    AFN e =AFN();
    e.AFN_UnionEspecial(a1,10,a13.Contador);
    e.AFN_UnionEspecial(a2,20,a13.Contador);
    e.AFN_UnionEspecial(a3,30,a13.Contador);
    e.AFN_UnionEspecial(a4,40,a13.Contador);
    e.AFN_UnionEspecial(a5,50,a13.Contador);
    e.AFN_UnionEspecial(a6,60,a13.Contador);
    e.AFN_UnionEspecial(a7,70,a13.Contador);
    e.AFN_UnionEspecial(a8,80,a13.Contador);
    e.AFN_UnionEspecial(a9,90,a13.Contador);
    e.AFN_UnionEspecial(a10,100,a13.Contador);
    e.AFN_UnionEspecial(a13,110,a13.Contador);
    //e.AFN_UnionEspecial(a26,120,a13.Contador);
    AFD nuevo = AFD();
    nuevo = nuevo.Conv_AFNaAFD(e);
    nuevo.Crea_TablaAFD();
    nuevo.Guarda_TablaAFD("ER_AFN");

    AFD  nuevo = AFD();
    nuevo.Carga_TablaAFD("ER_AFN.txt");

    ER_AFN e = ER_AFN("[a-z]|[A-Z]|[0-9]|((\\\\)&(\\||\\&|\\+|\\*|\\?|\\(|\\)|\\[|\\]|\\-|\\\\))",nuevo);

    if(e.IniConversion()){
        cout<<"Automata creado por Expresion regular"<<endl;
        e.result.Mx_Adyacencia(e.result);
    }else{
        cout<<"Expresion regular erronea"<<endl;
    }*/


    /*
    //Punto y coma (PC)
    AFN automata = AFN();
    AFN a1;
    a1 = automata.AFN_Basico(';',';',0);

    // FLECHA
    AFN automata2 = AFN();
    AFN a2;
    a2 = automata2.AFN_Basico('-','-',a1.Contador);

    AFN automata3 = AFN();
    AFN a3;
    a3 = automata3.AFN_Basico('>','>',a2.Contador);

    a2 = a2.AFN_Conca(a3);

    // OR
    AFN automata4 = AFN();
    AFN a4;
    a4 = automata4.AFN_Basico('|','|',a2.Contador);

    //SIMBOLO
    AFN automata5 = AFN();
    AFN a5;
    a5 = automata5.AFN_Basico('a','z',a4.Contador);

    AFN automata6 = AFN();
    AFN a6;
    a6 = automata6.AFN_Basico('A','Z',a5.Contador);

    AFN automata7 = AFN();
    AFN a7;
    a7 = automata7.AFN_Basico('0','9',a6.Contador);

    AFN automata8 = AFN();
    AFN a8;
    a8 = automata8.AFN_Basico('_','_',a7.Contador);

    a8 = a8.AFN_Union(a5);
    a8 = a8.AFN_Union(a6);
    a8 = a8.AFN_Union(a7);
    a8 = a8.AFN_CerrKleene();

    AFN automata9 = AFN();
    AFN a9;
    a9 = automata9.AFN_Basico('a','z',a8.Contador);

    AFN automata10 = AFN();
    AFN a10;
    a10 = automata10.AFN_Basico('A','Z',a9.Contador);

    a10 = a10.AFN_Union(a9);
    a10 = a10.AFN_Conca(a8);


    AFN automata11 = AFN();
    AFN a11;
    a11 = automata10.AFN_Basico(' ',' ',a11.Contador);

    AFN e =AFN();
    e.AFN_UnionEspecial(a11,2001,a11.Contador);
    e.AFN_UnionEspecial(a1,10,a11.Contador);
    e.AFN_UnionEspecial(a2,20,a11.Contador);
    e.AFN_UnionEspecial(a4,30,a11.Contador);
    e.AFN_UnionEspecial(a10,40,a11.Contador);

    AFD nuevo = AFD();
    nuevo = nuevo.Conv_AFNaAFD(e);
    nuevo.Crea_TablaAFD();
    nuevo.Guarda_TablaAFD("AFD_GramGram");*/



    /*NOTA: falta agregar más simbolos para no tener problemas
    agregacelos lo más pronto posible
    Clase III - 18
    Probar FIrst
    */

    //Gamaticas de Gramaticas
    /*AFD  nuevo = AFD();
    nuevo.Carga_TablaAFD("AFD_GramGram.txt");

    AnalizLexico l = AnalizLexico("E -> T Ep; Ep -> mas T Ep| epsilon;",nuevo);
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;
    cout<<l.yylex()<<" -> "<<l.Lexema<<endl;*/


    //Descenso recursivo mapeo de Gramatica
       /*= DescRecGram_Gram("E -> T Ep; Ep -> mas T Ep| menos T Ep |epsilon; T -> F Tp; Tp -> prod F Tp | div F Tp | epsilon; F -> parI E parD | num;","AFD_GramGram.txt");

    if(e.AnalizarGramatica()){
        cout<<"Expresion correcta"<<endl;
        e.IdentificarTerminales();
        cout<<"----Simbolos no terminales----"<<endl;
        int i=0;
        for(ClaseNodo s: e.Vn){
            cout<<"["<<i<<"] --> "<< s.Simbolo<< endl;
            i++;
        }//for
        cout<<"----------------------------"<<endl;

        cout<<"----Simbolos  terminales----"<<endl;
        int j=0;
        for(ClaseNodo n: e.Vt){
            cout<<"["<<j<<"] --> "<< n.Simbolo<< endl;
            j++;
        }//for
        cout<<"--------------------------"<<endl;

        cout<<"----Gramatica mapeada----"<<endl;
        i=0;
        for(int k=0; k<e.NumReglas ; k++){
                cout<<"Regla ["<<k<<"]:"<<e.ArrReglas[k].InfSimbolo.Simbolo<<endl;
            for(ClaseNodo p: e.ArrReglas[k].ListaLadoDerecho){
                cout<<"\t["<<i<<"] -->"<< p.Simbolo<<" -->EsTerminal: "<<p.Terminal<<"  ";
                i++;
            }
            cout<<endl;
        }//for
        cout<<"--------------------------"<<endl;
    }else{
        cout<<"Expresion erronea"<<endl;
    }

*/
