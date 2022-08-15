//Projeto Interdiciplinar: Matemática Computacional - Estudo Dirigido 01
//Simulador do jogo Craps
//Craps game simulator in C++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand((int)time(0)); //Inicia a funcao rand
    int flagponto1=0,flagponto2 = 0; //Marca a rodada em que esta o jogo
    int ponto1=0,ponto2=0;
    int result1=0,result2=0,result3=0,result4 = 0;

    while(1)
    {
        cout << ""<< endl;
        cout <<"Jogador 1, pressione uma tecla para jogar os dados"<< endl;

         result1= (rand() % 6) + 1; //Divisão por (6)+1
         result2= (rand() % 6) + 1;

        getchar();
        cout << "O valor do primeiro dado é: "<< result1<< endl;
        cout << "O valor do segundo dado é: "<< result2<< endl;

        if((result1+result2 == 7 && flagponto1 == 0) ||(result1+result2 == 11 && flagponto1 == 0) || (flagponto1 ==1 && result1+result2 == ponto1))
        {
         cout <<"Jogador 1, você venceu o jogo!";
         break;
        }

        if(((result1+result2==2 || result1+result2==3 || result1+result2==12) && flagponto1 == 0) || (result1+result2 == 7 && flagponto1 == 1) )
        {
          cout <<"Jogador 1, voce perdeu o jogo!";
          break;
        }

        else
        {
            if(flagponto1==0)
            {
             ponto1= result1+result2;
             flagponto1=1;
             cout << "Jogador 1, seu ponto é: " << ponto1 <<endl;
             cout << "" << endl;
            }

        }
        cout << ""<< endl;
        cout <<"Jogador 2 pressione uma tecla para jogar os dados"<< endl;
        result3= (rand() % 6) + 1;
        result4= (rand() % 6) + 1;

        getchar();
        cout << "Jogador 2, valor do primeiro dado é: "<< result3<< endl;
        cout << "Jogador2, o valor do segundo dado é: "<< result4<< endl;

        if((result3+result4 == 7 && flagponto2 == 0) ||(result3+result4 == 11 && flagponto2 == 0) || (flagponto2 ==1 && result3+result4 == ponto2))
        {
         cout <<"Jogador 2, voce venceu o jogo!";
         break;
        }

        if(((result3+result4==2 || result3+result4==3 || result3+result4==12) && flagponto2 == 0) || (result3+result4 == 7 && flagponto2 == 1) )
        {
          cout <<"Jogador 2, voce perdeu o jogo!";
          break;
        }

        else
        {
            if(flagponto2==0)
            {
             ponto2= result3+result4;
             flagponto2=1;
             cout << "Jogador2, seu ponto é: " << ponto2 <<endl;
             cout << "" << endl;
            }
        }
    }
}
