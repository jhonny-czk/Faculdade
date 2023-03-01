#ifndef CONTA_H
#define CONTA_H

#include <iostream>
using namespace std;

class Conta{
private:
    int _numero;
    int _agencia;
    int _saldo;
    
public:
    Conta(int numero, int agencia) : _numero(numero), _agencia(agencia), _saldo(0) {}
    //~Conta();

    void deposita(float quantia)
    {
        _saldo += int(quantia * 100); // x100 p/ transformar em centavos
        
        //Obs.: Conversão de Float p/ Int p/ evitar o problema de 
        // "imprecisão" do float, com o acumulo do vale das casas decimais 
        // Isso ocorre com Float e Double, e não com os tipos Decimal, BigDecimal, Numeric, etc
    }

    void saque(float quantia)
    {
        _saldo -= int(quantia * 100);
    }

    void transfere(float valor, Conta* contaDestino) 
    {
        contaDestino->deposita(valor);
        saque(valor);
    }

    float getSaldo()
    {
        return _saldo / 100.0f;
    }

    void imprimeExtrato()
    {
        cout << "CONTA....: " << _numero << endl;
        cout << "AGENCIA..: " << _numero << endl;
        cout << "SALDO....: " << getSaldo()  << endl;
    }
};

#endif //CONTA_H