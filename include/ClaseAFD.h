#ifndef CLASEAFD_H
#define CLASEAFD_H
#include "ClaseAFN.h"
#include "ConIj.h"
#include <vector>
#include <stack>



class AFD{
    public:
        std::vector<int> flag;
        std::vector<char> Alfabeto; //Alfabeto propio del automata
        //Matriz de adyacencia para el AFD
        int **Mx_adyacencia;
    private:
        std::vector<ConIj> EdoAFD; //Conjunto de estados
        std::vector<ConIj> EdoAcept; //Conjunto de estados de aceptacion
        int EdoIni;//ID del estado inicial
        int IdAFD; //identificadro del Automata
    public:
        //Constructor de AFD
        AFD();
        //Regresa el conjunto de Estados del AFD
        std::vector<ConIj> get_EdoAFN ();

        //Agrega una estado al conjunto de estados del AFD
        void set_EdoAFN (ConIj e);

        //Agrega el conjutno de estados al conjunto de estados del AFD
        void set_EdoAFN (std::vector<ConIj> Conj);

        //Regresa el Alfabeto
        std::vector<char> get_Alfabeto ();

        //Añade un simbolo al alfabeto
        void set_Alfabeto(char simb);

        //Regresa el conjunto de estados de aceptacion
        std::vector<ConIj> get_EdoAcept();

        //Añade un estado al conjunto de estados de aceptacion
        void set_EdoAcept (ConIj e);

        //Regresa el ID del estado inicial
        int get_EdoIni();

        //Establece el estado inicial(ID)
        void set_EdoIni(int IdEdoIni);

        //Regresa el ID del AFD
        int get_IdAFD();

        //Establece el ID del AFD
        void set_IdAFD(int ID);

        //Convierte un AFD (Con union especial) a un AFD
        AFD Conv_AFNaAFD (AFN automata);

        //Establece la tabla de adyacencia correspondiente al AFD (this)
        void Crea_TablaAFD ();

        //Guardar

        //Analisis de cadenas

        //yylex()

        //Destructor
        virtual ~AFD();

};

#endif // CLASEAFD_H
