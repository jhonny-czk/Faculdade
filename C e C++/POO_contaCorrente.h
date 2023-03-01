#ifndef CONTA_CORRENTE_H
#define CONTA_CORRENTE_H

#include "conta.h"

class ContaCorrente : public Conta{    
public:
    ContaCorrente(int numero, int agencia) : Conta(numero, agencia) {}
    //~ContaCorrente();
}; 
// Na herança, todos os metodos são herdados, porem nem todos são visíveis.
// O metodo contrutor é herdado, mas não é externalizado. 
// Por isso é preciso declarar o contrutor novamente.

// Em C++ existem os modificadores de herança Public, Protected e Private.
//  O modificador Public resolve a maioria dos casos
//  Protected é usado quando se quer que o filho herde sem externalizar para demais decendentes

//Modificador de heranca:
//  - public: 
//      classe pai public    -> public na classe filho 
//      classe pai protected -> protected classe filho  
//      classe pai private   -> classe filho (não acessa)

#endif //CONTA_CORRENTE_H