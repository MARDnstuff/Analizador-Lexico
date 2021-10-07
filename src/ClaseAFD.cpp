#include "ClaseAFD.h"


//---FUNCIONES AUXILIARES---

//Regresa el estado por ID, que se encuentra dentro del vector
Estado DameEdo_byID_AFD(std::vector<Estado> Edo,int EdoID){
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

//Regresa el estado por ID, que se encuentra dentro del vector
ConIj DameConIj_byID_AFD(std::vector<ConIj> Edo,int EdoID){
    int tam = (int) Edo.size();
    for(int i=0; i<tam;i++){
        if(Edo.at(i).get_ConIj_ID() == EdoID){
            return Edo.at(i);
        }//if
    }//for
    ConIj e = ConIj();
    return e;
}

//Verifica si el simbolo ya esta en el alfabeto
bool ContieneSimb_AFD(std::vector<char> Alf,char simb){
    int tam = (int) Alf.size();
    if(Alf.empty()){
        return false;
    }

    for(int i=0;i<tam;i++){
        if(Alf.at(i) == simb)
            return true;
    }//for
    return false;
}
//Verifica que se encuentre el elemento dentro del arreglo
bool ContieneElem(std::vector<Estado> Conjunto,int IdEdo){
    int tam = (int) Conjunto.size();
    for(int i=0; i<tam;i++){
        if(IdEdo == Conjunto.at(i).get_IdEstado()){
            return true;
        }//if
    }//for
    return false;
}


////////////////////////////////////////////
//--METODOS CLASE AFD

//Constructor de AFD
AFD::AFD(){
    EdoAFD.clear();
    EdoAcept.clear();
    Alfabeto.clear();
    EdoIni = -1;
    IdAFD = -1;
    //ctor
}
//Regresa el conjunto de Estados del AFD
std::vector<ConIj> AFD:: get_EdoAFN (){
    return EdoAFD;
}

//Agrega una estado al conjunto de estados del AFD
void AFD::set_EdoAFN (ConIj e){
    EdoAFD.push_back(e);
    return;
}

//Agrega el conjutno de estados al conjunto de estados del AFD
void AFD:: set_EdoAFN (std::vector<ConIj> Conj){
    EdoAFD = Conj;
    return;
}

//Regresa el Alfabeto
std::vector<char> AFD:: get_Alfabeto (){
    return Alfabeto;
}

//Añade un simbolo al alfabeto
void AFD:: set_Alfabeto(char simb){
    if(Alfabeto.empty() || !ContieneSimb_AFD(Alfabeto,simb)){
        Alfabeto.push_back(simb);
    }
    return;
}

//Regresa el conjunto de estados de aceptacion
std::vector<ConIj> AFD:: get_EdoAcept(){
    return EdoAcept;
}

//Añade un estado al conjunto de estados de aceptacion
void AFD:: set_EdoAcept (ConIj e){
    EdoAcept.push_back(e);
}

//Regresa el ID del estado inicial
int AFD:: get_EdoIni(){
    return EdoIni;
}

//Establece el estado inicial(ID)
void AFD:: set_EdoIni(int IdEdoIni){
    EdoIni = IdEdoIni;
    return;
}

//Regresa el ID del AFD
int AFD:: get_IdAFD(){
    return IdAFD;
}

//Establece el ID del AFD
void AFD::set_IdAFD(int ID){
    IdAFD = ID;
    return;
}


//Convierte un AFD (Con union especial) a un AFD
AFD AFD :: Conv_AFNaAFD (AFN automata){
    int Contador =0,tam_Alf= (int) automata.Alfabeto.size();
    int tam_Stack;
    std::vector<ConIj> Estados; //auxiliar

    //Conjuntos Si para analizar
    std::vector<ConIj> Si;
    //Conjuntos sin analizar
    std::stack<ConIj> Nuevo_Si;

    //1) Cerradura epsilon del Estado inicial
    ConIj Sj = ConIj();
    Sj.set_ConIj_ID(0);
    Sj.set_ConIJ_Edos(automata.CerraduraEpsilon(DameEdo_byID_AFD(automata.EdoAFN,automata.EdoIni)));
    //2) Añadimos S0 al conjunto sin analizar y al conjunto para analizar
    Si.push_back(Sj);
    Nuevo_Si.push(Sj);
    tam_Stack = (int) Nuevo_Si.size();
    Contador++;

    //3) Empieza proceso de analisis para cada uno de lo elemenots Si y los nuevos que se vayan creando
    ConIj aux,aux2;
    std::vector<Estado> temp;

   while(tam_Stack != 0){
        aux = Nuevo_Si.top();
        Nuevo_Si.pop();

        for(int i=0; i<tam_Alf; i++){
                if(automata.Alfabeto.at(i) == EPSILON){
                    continue;
                }
            temp = automata.Ir_A(aux.get_ConIj_Edos(),automata.Alfabeto.at(i));
            if(temp.empty()){continue;}
            //Caso en el que sea un nuevo Conjunto
            int IDdestino = aux.equals_to(Si,temp);
            if(IDdestino < 0){
                aux2.set_ConIJ_Edos(temp);
                aux2.set_ConIj_ID(Contador);
                Contador++;
                Si.push_back(aux2);
                Nuevo_Si.push(aux2);
            }else{
                aux2.set_ConIj_ID(Si.at(IDdestino).get_ConIj_ID());
                aux2.set_ConIJ_Edos(temp);
            }
            Transicion  t = Transicion(automata.Alfabeto.at(i),aux.get_ConIj_ID(),aux2.get_ConIj_ID());
            aux.Trans1.push_back(t);

        }//for

        Estados.push_back(aux);
        tam_Stack = (int) Nuevo_Si.size();
            //break;

    }//while

    //Falta establecer el conjunto de estados de aceptacion
    int tam = Estados.size(),tam_a = (int) automata.EdoAcept.size();;
    for(int i=0; i<tam;i++){
            for(int n =0; n<tam_a; n++){
                if(ContieneElem(Estados.at(i).get_ConIj_Edos(),automata.EdoAcept.at(n).get_IdEstado())){
                    Estados.at(i).Acept =true;
                    Estados.at(i).Token = automata.EdoAcept.at(n).get_Token();
                    EdoAcept.push_back(Estados.at(i));
                }//if
            }//for
    }//for

    EdoAFD = Estados;
    Alfabeto = automata.Alfabeto;
    EdoIni = 0;
    IdAFD=300;
    return *this;

}
/////bug
//Establece la tabla de adyacencia correspondiente al AFD (this)
void AFD :: Crea_TablaAFD (){
    int m = (int) EdoAFD.size();
    Mx_adyacencia = new int*[m];
    for(int i=0; i<m; i++){
        Mx_adyacencia[i] = new int[258];
    }//for

    //inicializamos todo con -1
    for(int i=0; i<m;i++){
        for(int j=0; j< 258; j++){
            Mx_adyacencia[i][j] = -1;
        }//for
    }//for

    ConIj aux;
    int tam = (int) EdoAFD.size(),tam_;
    Transicion t;

    for(int n=0; n<tam; n++){
        aux = DameConIj_byID_AFD(EdoAFD,n);
        flag.push_back(aux.Token);
        tam_ = (int) aux.Trans1.size();
        for(int m =0; m<tam_;m++){
            int simb_pos = (int) aux.Trans1.at(m).get_SimbInf();
            Mx_adyacencia[n][simb_pos] = aux.Trans1.at(m).get_EdoDestino();
           // std::cout<<"["<<n<<"]"<<"["<<simb_pos<<"]-->"<<aux.Trans1.at(m).get_EdoDestino()<<std::endl;
        }//for
         /*if(aux.Acept){
                Mx_adyacencia[n][257] = aux.Token;

            }else{
                Mx_adyacencia[n][257] =0;
            }*/
    }//for

    return;
}


AFD::~AFD(){
    //dtor
}
