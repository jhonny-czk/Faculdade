#include <iostream>
#include "contaCorrente.h"

using namespace std;

int main()
{
    //Exemplo de uso das classes
    ContaCorrente c1(1234, 9999);
    c1.deposita(1000);
    c1.saque(100);
    c1.imprimeExtrato();
      
    return 0;
}