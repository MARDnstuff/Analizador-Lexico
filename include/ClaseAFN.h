#ifndef CLASEAFN_H
#define CLASEAFN_H
#include <iostream>
#include "ClaseEstado.h"
#include <vector>

class AFN{

    public: //private:
        int aux;
        int Contador;
        int EdoIni;
        std::vector<Estado> EdoAFN;
        std::vector<Estado> EdoAcept;
        std::vector<char> Alfabeto;
        //bool SeAgregoAFNUnionLexico; //sin informacion por el momento
        int IdAFN;
    public:
        //Constructor del AFN
        AFN();
        //Crea un AFN basico para un simbolo
        AFN AFN_Basico (char simb,int Cont);
        //Crea un AFN Basico para un rango de caracteres
        AFN  AFN_Basico (char simb1,char simb2,int Cont);
        //Union de dos AFN
        AFN AFN_Union (AFN automata);
        //Concatenación de  dos AFN
        AFN AFN_Conca (AFN automata);
        //Cerradura positiva de un AFN
        AFN AFN_CerrPOS();
        //Cerradura de Kleene
        AFN AFN_CerrKleene();
        //Operacion opcional (?)
        AFN AFN_Opcional();
        //Regresa el conjunto de estado que son accesible desde "e" con EPSILON
        std::vector<Estado> CerraduraEpsilon(Estado e);

       //Regresa el contador del ultimo estado creado
       int get_Contador ();
       //Muestra la matriz de adyacencia del AFN
       void Mx_Adyacencia(AFN automata);

        virtual ~AFN();


};

#endif // CLASEAFN_H
