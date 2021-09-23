#include "SimbolosEspeciales.h"
#include "ClaseAFN.h"
#include "ClaseEstado.h"
#include "ClaseTransicion.h"

//Constructor del AFN
AFN::AFN(){
    IdAFN = 0;
    EdoIni = -1;//posible error
    EdoAFN.clear();
    EdoAcept.clear();
    Alfabeto.clear();
    //SeAgregoAFNUnionLexico = false; //sin información por el momento
    //ctor
}

//Crea un AFN basico para un simbolo
AFN AFN :: AFN_Basico (char simb, int Cont){
    AFN temp = AFN();
    int Origen=Cont,Destino = Cont+1;
    Estado e1, e2;
    e1 = Estado();
    e1.set_IdEstado(Origen);
    e2 = Estado();
    e2.set_IdEstado(Destino);

    Transicion t = Transicion(simb,Origen,Destino);
    Transicion t2 = Transicion();
    Contador=Destino+1;
    e1.set_Trans(t);
    e2.set_EdoAcept(true);
    e2.set_Trans(t2);
    temp.Alfabeto.push_back(simb);
    temp.EdoIni = e1.get_IdEstado();
    temp.EdoAFN.push_back(e1);
    temp.EdoAFN.push_back(e2);
    temp.EdoAcept.push_back(e2);
    temp.Contador = Destino+1;
    //SeAgregoAFNUnionLexico = false; //sin información por el momento
    return temp;
}

//Crea un AFN Basico para un rango de caracteres
AFN AFN :: AFN_Basico (char simb1,char simb2,int Cont){
    AFN temp = AFN();
    int Origen=Cont,Destino = Cont+1;
    Estado e1, e2;
    e1 = Estado();
    e1.set_IdEstado(Origen);
    e2 = Estado();
    e2.set_IdEstado(Destino);
    int s1 = (int) simb1,s2 = (int) simb2;
    while(s1<=s2 ){
        char s = (char) s1;
        Transicion t = Transicion(s,Origen,Destino);
        Transicion t2 = Transicion();
        e1.set_Trans(t);
        //e2.set_Trans(t2);
        s1++;
    }//for

    Contador=Destino+1;
    e2.set_EdoAcept(true);
    int m = simb1,n = simb2;
    while(m<=n){
        char s = m;
        temp.Alfabeto.push_back(s);
        m++;
    }

    temp.EdoIni = e1.get_IdEstado();
    temp.EdoAFN.push_back(e1);
    temp.EdoAFN.push_back(e2);
    temp.EdoAcept.push_back(e2);
    temp.Contador = Destino+1;
    //SeAgregoAFNUnionLexico = false; //sin información por el momento
    return temp;

}

//Union de dos AFN
AFN AFN :: AFN_Union (AFN automata){

    int Origen= automata.get_Contador();
    int Destino=Origen+1;
    Estado e1,e2;
    e1 = Estado();
    e1.set_IdEstado(Origen);
    e2 = Estado();
    e2.set_IdEstado(Destino);
    //Estas transiciones le pertencen a e1
    Transicion t1 = Transicion(EPSILON,Origen,EdoIni);
    Transicion t2 = Transicion(EPSILON,Origen,automata.EdoIni);
    e1.set_Trans(t1);
    e1.set_Trans(t2);

    int tam = (int) EdoAFN.size();
    for(int i=0;i<tam;i++){
        if(EdoAFN.at(i).is_EdoAcept()){
            Transicion t = Transicion(EPSILON,EdoAFN.at(i).get_IdEstado(),e2.get_IdEstado());
            EdoAFN.at(i).set_EdoAcept(false);
            EdoAFN.at(i).set_Trans(t);
        }//if

    }//for

    int tam2 =(int) automata.EdoAFN.size();
    for(int i=0;i<tam2;i++){
        if(automata.EdoAFN.at(i).is_EdoAcept()){
            Transicion t_ = Transicion(EPSILON,automata.EdoAFN.at(i).get_IdEstado(),e2.get_IdEstado());
            automata.EdoAFN.at(i).set_EdoAcept(false);
            automata.EdoAFN.at(i).set_Trans(t_);
        }//if

    }//for
Contador=Destino+1;
    //actulizamos informacion para el automata resultante
    EdoAcept.clear();
    automata.EdoAcept.clear();
    EdoIni = e1.get_IdEstado();
    e2.set_EdoAcept(true);
    EdoAcept.push_back(e2);


    //Union de los estados de los dos automatas
    int n = (int) automata.EdoAFN.size();
        for (int i=0;i<n;i++){
            EdoAFN.push_back(automata.EdoAFN.at(i));
            //Transicion m = Transicion();
        }//for
    //Unions de los alfabetos de los automatas
    int p = (int) automata.Alfabeto.size();
    for(int i=0;i<p;i++){
        Alfabeto.push_back(automata.Alfabeto.at(i));
    }//for

    EdoAFN.push_back(e1);
    EdoAFN.push_back(e2);


    return *this;

}

//Concatenación de  dos AFN
AFN AFN :: AFN_Conca (AFN automata){
    std::vector<Transicion> t1;
    std::vector<Transicion> t2;
    int nuevoID = automata.EdoIni, viejoID = EdoAcept.at(0).get_IdEstado();
    int p = (int) EdoAFN.size(),cn;

   int n = (int) automata.EdoAFN.size();
    for(int i=0;i<n;i++){
        if(automata.EdoAFN.at(i).get_IdEstado() == automata.EdoIni){
            t1 = automata.EdoAFN.at(i).get_Trans();
            automata.EdoAFN.erase(automata.EdoAFN.begin()+i);
            break;
        }//if
    }//for


    int q = (int) t1.size();
    for(int i=0;i<p;i++){
        if(EdoAFN.at(i).is_EdoAcept()){
            EdoAFN.at(i).set_EdoAcept(false);
            EdoAFN.at(i).set_IdEstado(nuevoID);
           for(int j=0;j<q;j++){
                EdoAFN.at(i).set_Trans(t1.at(j));
            }//for
        }
    }//for

    EdoAcept.clear();
    EdoAcept.push_back(automata.EdoAcept.at(0));

    int lim = (int) automata.EdoAFN.size();
    for(int i=0;i<lim;i++){
        EdoAFN.push_back(automata.EdoAFN.at(i));
    }//for

    int llim = (int) EdoAFN.size();

    for(int i=0;i<llim;i++){
        cn = (int) EdoAFN.at(i).get_Trans().size();
        for(int j=0;j<cn;j++){
            if(EdoAFN.at(i).get_Trans().at(j).get_EdoDestino() == viejoID){
                EdoAFN.at(i).Trans1.at(j).set_EdoDestino(nuevoID);
            }
        }//for
    }//for

    Contador=automata.Contador;

    return *this;

}

//Cerradura positiva de un AFN
AFN AFN ::AFN_CerrPOS(){
    int Origen=Contador,Destino=Origen + 1;
    Estado e1,e2;
    e1 = Estado();//nuevo estado inicial
    e1.set_IdEstado(Origen);
    e2 = Estado();//nuevo estado final
    e2.set_IdEstado(Destino);


    int n = (int) EdoAFN.size();
    for(int i=0; i<n; i++){
        if(EdoAFN.at(i).is_EdoAcept()){
            Transicion t = Transicion(EPSILON,EdoAFN.at(i).get_IdEstado(),EdoIni);
            Transicion t1 = Transicion(EPSILON,EdoAFN.at(i).get_IdEstado(),Destino);
            EdoAFN.at(i).set_Trans(t);
            EdoAFN.at(i).set_EdoAcept(false);
            EdoAFN.at(i).set_Trans(t1);
            break;
        }//if
    }//for

    Transicion t2 = Transicion(EPSILON,e1.get_IdEstado(),EdoIni);
    e1.set_Trans(t2);

    EdoAcept.clear();
    e2.set_EdoAcept(true);
    EdoAcept.push_back(e2);

    EdoIni = e1.get_IdEstado();
    EdoAFN.push_back(e1);
    EdoAFN.push_back(e2);
    Contador=Destino + 1;

    return *this;

}

//Cerradura de Kleene
AFN AFN :: AFN_CerrKleene(){
    int Origen=Contador,Destino=Origen + 1;
    Estado e1,e2;
    e1 = Estado();//nuevo estado inicial
    e1.set_IdEstado(Origen);
    e2 = Estado();//nuevo estado final
    e2.set_IdEstado(Destino);


    int n = (int) EdoAFN.size();
    for(int i=0; i<n; i++){
        if(EdoAFN.at(i).is_EdoAcept()){
            Transicion t = Transicion(EPSILON,EdoAFN.at(i).get_IdEstado(),EdoIni);
            Transicion t1 = Transicion(EPSILON,EdoAFN.at(i).get_IdEstado(),e2.get_IdEstado());
            EdoAFN.at(i).set_Trans(t);
            EdoAFN.at(i).set_EdoAcept(false);
            EdoAFN.at(i).set_Trans(t1);
            break;
        }//if
    }//for

    Transicion t2 = Transicion(EPSILON,e1.get_IdEstado(),EdoIni);
    Transicion t3 = Transicion(EPSILON,e1.get_IdEstado(),Destino);
    e1.set_Trans(t2);
    e1.set_Trans(t3);

    EdoAcept.clear();
    e2.set_EdoAcept(true);
    EdoAcept.push_back(e2);

    EdoIni = e1.get_IdEstado();
    EdoAFN.push_back(e1);
    EdoAFN.push_back(e2);
    Contador=Destino + 1;
    return *this;
}

//Operacion opcional (?)
AFN AFN :: AFN_Opcional(){
    int Origen=Contador,Destino=Origen + 1;
    Estado e1,e2;
    e1 = Estado();//nuevo estado inicial
    e1.set_IdEstado(Origen);
    e2 = Estado();//nuevo estado final
    e2.set_IdEstado(Destino);


    int n = (int) EdoAFN.size();
    for(int i=0; i<n; i++){
        if(EdoAFN.at(i).is_EdoAcept()){
            Transicion t1 = Transicion(EPSILON,EdoAFN.at(i).get_IdEstado(),Destino);
            EdoAFN.at(i).set_EdoAcept(false);
            EdoAFN.at(i).set_Trans(t1);
            break;
        }//if
    }//for

    Transicion t2 = Transicion(EPSILON,e1.get_IdEstado(),EdoIni);
    Transicion t3 = Transicion(EPSILON,e1.get_IdEstado(),Destino);
    e1.set_Trans(t2);
    e1.set_Trans(t3);

    EdoAcept.clear();
    e2.set_EdoAcept(true);
    EdoAcept.push_back(e2);

    EdoIni = e1.get_IdEstado();
    EdoAFN.push_back(e1);
    EdoAFN.push_back(e2);
    Contador=Destino + 1;


    return *this;
}


//Muestra la matriz de adyacencia del AFN
void AFN :: Mx_Adyacencia(AFN automata){
int tam = (int) automata.EdoAFN.size();


    for(int i=0; i< tam ; i++){
        std::cout<<"ESTADO --> Q"<<automata.EdoAFN.at(i).get_IdEstado()<<"\n";
        int alf = (int) automata.EdoAFN.at(i).get_Trans().size();
        if(automata.EdoAFN.at(i).get_Trans().empty()){
            std::cout<<"SIN TRANCISION\n";
            std::cout<<"Estado de aceptacion: "<<automata.EdoAFN.at(i).is_EdoAcept()<<"\n";
        }else{
            for(int j=0; j<alf;j++){
                std::cout<<"TRANSICIONES\n";
                std::cout<<"De Q"<<automata.EdoAFN[i].get_IdEstado()<<" --> Q"<<automata.EdoAFN[i].get_Trans().at(j).get_EdoDestino()<<"\n";
                std::cout<<"Caracter necesario: "<<automata.EdoAFN.at(i).get_Trans().at(j).get_SimbInf()<<"\n";
                std::cout<<"Estado de aceptacion: "<<automata.EdoAFN.at(i).is_EdoAcept()<<"\n";
            }//for
        }//if

    }//for


}


//Regresa el contador del ultimo estado creado
int AFN :: get_Contador (){
    return Contador;
}

AFN::~AFN(){
    //dtor
}
