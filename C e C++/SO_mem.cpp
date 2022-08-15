// Sistemas Operacionais
//Algoritmo de alocação de memória FirstFit e Bestfit
#include<iostream>
#include<cstring>
#include<string>
using namespace std;

void firstFit(int tamBloco[], int m, int tamProcesso[], int n)
{
    int alocacao[n]; //bloco alocado para processo
    memset(alocacao, -1, sizeof(alocacao)); // Nenhum bloco esta inicialmente 
										                       //alocado a nenhum processo 
 
    // escolhe um processo e encontra um bloco que encaixa
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (tamBloco[j] >= tamProcesso[i])
            {
                // aloca o bloco j no processo [i] 
                alocacao[i] = j;
 
                // Reduz a memoria disponível no bloco
                tamBloco[j] -= tamProcesso[i];
 
                break;
            }
        }
    }
 
    cout << "\nNo Processo.\tTamanho Processo\tNo do Bloco.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i+1 << "\t\t"
             << tamProcesso[i] << "\t\t";
        if (alocacao[i] != -1)
            cout << alocacao[i] + 1;
        else
            cout << "Não alocado";
        cout << endl;
    }
}
 
void bestFit(int tamBloco[], int m, int tamProcesso[], int n)
{
    int alocacao[n];
    memset(alocacao, -1, sizeof(alocacao)); // Nenhum bloco esta inicialmente 
										                       //alocado a nenhum processo 

	// escolhe cada processo e encontra um bloco que encaixa de acordo com o tamanho
    for (int i=0; i<n; i++)
    {
        //Procura o melhor bloco para o processo que esta para ser alocado
        int melhorEncaixe = -1;
        for (int j=0; j<m; j++)
        {
            if (tamBloco[j] >= tamProcesso[i])
            {
                if (melhorEncaixe == -1)
                    melhorEncaixe = j;
                else if (tamBloco[melhorEncaixe] > tamBloco[j])
                    melhorEncaixe = j;
            }
        }

        if (melhorEncaixe != -1) //Caso nao encontre um bloco para o processo atual
        {
            // Aloca o bloco j no processo [i] 
            alocacao[i] = melhorEncaixe;

            // Reduz a memoria disponível no bloco
            tamBloco[melhorEncaixe] -= tamProcesso[i];
        }
    }

    cout << "\nNumero Processo.\tTamanho Processo Size\tNumero Bloco.\n";
    for (int i = 0; i < n; i++)
    {
        cout << "   " << i+1 << "\t\t" << tamProcesso[i] << "\t\t";
        if (alocacao[i] != -1)
            cout << alocacao[i] + 1;
        else
            cout << "Não Alocado";
        cout << endl;
    }
}


int main()
{
    int tamBloco[] = {100, 500, 200, 300, 600};
    int tamProcesso[] = {212, 417, 112, 426};
    int m = sizeof(tamBloco) / sizeof(tamBloco[0]);
    int n = sizeof(tamProcesso) / sizeof(tamProcesso[0]);
    /*Descomentar o algoritmo que será usado*/
    //firstFit(tamBloco, m, tamProcesso, n);
    //bestFit(tamBloco, m, tamProcesso, n);
    return 0 ;
}
