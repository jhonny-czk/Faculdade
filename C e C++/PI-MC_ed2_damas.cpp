////Projeto Interdiciplinar: Matemática Computacional - Estudo Dirigido 02
//Sobre: Trabalho de jogo de Damas em C++ (com modificações)
//About: Checkers game in C++ (with modifications) for college assignments 
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <math.h>
using namespace std;
int numAleatorio,numB,numP,valorB,valorP;
int l,c,linhaDestino,colunaDestino;
bool fimTurnoBranco,fimTurnoPreto;
int PontoJogadorBranco, PontoJogadorPreto;
char jogadorBranco(char tabuleiro[9][9]) , jogadorPreto(char tabuleiro[9][9]) ;
char tabuleiro[9][9]= {
    {'0','1','2','3','4','5','6','7','8'},
    {'1','_','B','_','B','_','B','_','B'},
    {'2','B','_','B','_','B','_','B','_'},
    {'3','_','B','_','B','_','B','_','B'},
    {'4','_','_','_','_','_','_','_','_'},
    {'5','_','_','_','_','_','_','_','_'},
    {'6','P','_','P','_','P','_','P','_'},
    {'7','_','P','_','P','_','P','_','P'},
    {'8','P','_','P','_','P','_','P','_'},
    };
char mostrarTabuleiro (char tabuleiro[9][9]) //Funcao com nome autoexplicativo
{
    for (l=0;l<9;l++)
    {
       for (c=0;c<9;c++)
       {
            cout << tabuleiro[l][c] << " ";
       }
        cout << "\n";
    }
return tabuleiro[9][9];
}

char atualizaTabuleiro(char tabuleiro[9][9]) //Outra funcao com nome autoexplicativo
{
    system("cls"); //limpa tela
    for (l=0;l<9;l++)
    {
       for (c=0;c<9;c++)
       {
            cout << tabuleiro[l][c] << " ";
       }
        cout << "\n";
    }
}
char vencedor (char tabuleiro[9][9])//Dizer quem ganhou o jogo
{
    PontoJogadorBranco = 0;
    PontoJogadorPreto = 0;
    for (l=0;l<9;l++)
    {
       for (c=0;c<9;c++)
       {
           if (tabuleiro[l][c] == 'B')
           {
               PontoJogadorBranco++;
           }
           else if (tabuleiro[l][c] == 'P')
           {
               PontoJogadorPreto++;
           }
       }
    }
    if (PontoJogadorBranco == 0) //Se nao houver mais pecas brancas
    {
        system("CLS");
        cout << "\n";
        cout << " Vitoria das pecas pretas!!! \n";
        cout << "\n";
        mostrarTabuleiro(tabuleiro);
        exit(0);
    }
    else if (PontoJogadorPreto == 0)
    {
        system("CLS");
        cout << "\n";
        cout << " Vitoria das pecas pretas!!! \n";
        cout << "\n";
        mostrarTabuleiro(tabuleiro);
        exit(0);
    }
}

void fimTabuleiro()
{//quando uma peca chega ao final do tabuleiro
    for(c=1; c< 9; c++)
    {
        if (tabuleiro[1][c] == 'P')
        {
            tabuleiro[1][c] = '_';
        }//a peca some ao chegar na ultima linha
    }
    for(c=1; c<9; c++)
    {
        if (tabuleiro[8][c] == 'B')
        {
            tabuleiro[8][c] = '_';
        }
    }
}

char jogadorBranco (char tabuleiro[9][9])
{//Turno do jogador das pecas brancas
    l=0;
    c=0;
    mostrarTabuleiro(tabuleiro);
    cout << "\n";
    fimTurnoBranco = false;
    while(fimTurnoBranco == false)
    {
        pecaOrigem:
        cout << "Pecas brancas, escolha uma peca para movimentar.\n";
        cout << "Digite a linha da peca.\n";
        cin >> l;
        cout << "Digite a coluna da peca.\n";
        cin >> c;
        //Selecao da linha/coluna de origem
        while((tabuleiro[l][c] != 'B'))
        {//Enquato a peca de origem nao for selecionada corretamente
            cout << "Nao ha pecas brancas na linha na linha/coluna selecionados.\n";
            cout << "\n";
            goto pecaOrigem;
        }

        while ((tabuleiro[l][c] == 'B'))
        {//Selecao da linha coluna de destino
            pecaDestino:
            cout << "Pecas brancas, escolha um espaco para movimentar esta peca.\n";
            cout << "Digite a linha de destino.\n";
            cin >> linhaDestino;
            cout << "Digite a coluna de destino." << endl;
            cin >> colunaDestino;
            if((tabuleiro[l+1][c+1] == '_') && ( abs(l-linhaDestino)==1) && (abs(c-colunaDestino)==1))
            {
                tabuleiro[l+1][c+1] = 'B';
                tabuleiro[l][c] = '_';
                goto fimDoTurnoBranco;
            }
            else if ((tabuleiro[l+1][c-1] == '_') && ( abs(l-linhaDestino)==1) && (abs(c-colunaDestino)==1) )
            {
                tabuleiro[l+1][c-1] == 'B';
                tabuleiro[l][c] = '_';
                goto fimDoTurnoBranco;
            }
            else if(linhaDestino < 2)
            {// peca movendo na direcao inversa
                cout << "Movimento não permitido.\n";
                l=0;
                c=0;
                goto pecaOrigem;
            }
            /*else if (( abs(l-linhaDestino)!=1) && (abs(c-colunaDestino)!=1))
            {
                cout << "Movimento não permitido.\n";
                cout << "Os movimentos devem ser realizados na digonal.\n";
                l=0;
                c=0;
                goto pecaDestino;
            }*/
            else if (linhaDestino == l && ( abs(l-linhaDestino)==1) && (abs(c-colunaDestino)==1))
            {//peca movida fora da diagonal
                cout << "Movimento não permitido.\n";
                cout << "Os movimentos devem ser realizados na digonal.\n";
                l=0;
                c=0;
                goto pecaDestino;
            }
            else if ((colunaDestino == c) && ( abs(l-linhaDestino)==1) && (abs(c-colunaDestino)==1))
            {//peca movida fora da diagonal
                cout << "Movimento não permitido.\n";
                cout << "Os movimentos devem ser realizados na digonal.\n";
                l=0;
                c=0;
                goto pecaDestino;
            }
            else if((tabuleiro[l+1][c+1] == 'B'))
            {//peca nao pode ser movida pois existe outra peca no local
                cout << "Esta peca nao pode ser movida.\n";
                l=0;
                c=0;
                goto pecaOrigem;
            }
            else if ((tabuleiro[l+1][c-1] == 'B'))
            {
                cout << "Esta peca nao pode ser movida.\n";
                l=0;
                c=0;
                goto pecaOrigem;
            }
            while ((abs(l-linhaDestino)!=1) && (abs(c-colunaDestino)!=1))
            {
                if ((tabuleiro[l+1][c+1] == 'P') && (tabuleiro[l+2][c+2] == '_') && ( abs(l-linhaDestino)==2) && (abs(c-colunaDestino)==2))
                {//comer a peca adversaria
                    tabuleiro[l+2][c+2] = 'B';
                    tabuleiro[l+1][c+1] = '_';
                    tabuleiro[l][c] = '_';
                    break;
                }
                else if ((tabuleiro[l+1][c-1] == 'P') && (tabuleiro[l+2][c-2] == '_') && ( abs(l-linhaDestino)==2) && (abs(c-colunaDestino)==2))
                {//comer a peca adversaria
                    tabuleiro[l+2][c-2] = 'B';
                    tabuleiro[l+1][c-1] = '_';
                    tabuleiro[l][c] = '_';
                    break;
                }
                else if ((tabuleiro[l+1][c+1] == 'P') && (tabuleiro[l+2][c+2] != '_'))
                {//peça não pode ser comida pois não há espaços vazios atrás dela
                    cout << "Movimento invalido.\n";
                    cout << "Esta peca nao pode ser comida pois nao ha espaços vazios atras dela.\n";
                    goto pecaDestino;
                }
                else if ((tabuleiro[l+1][c-1] == 'P') && (tabuleiro[l+2][c-2] != '_'))
                {
                    cout << "Movimento invalido.\n";
                    cout << "Esta peca nao pode ser comida pois nao ha espaços vazios atras dela.\n";
                    goto pecaDestino;
                }
            }
        }
    fimDoTurnoBranco:
    fimTurnoBranco == true;
    fimTabuleiro();
    vencedor(tabuleiro);
    jogadorPreto(tabuleiro);
    }
}
//-------------------------------------
char jogadorPreto (char tabuleiro[9][9])
{ //Turno do jogador das pecas pretas
    l=0;
    c=0;
    mostrarTabuleiro(tabuleiro);
    cout << "\n";
    fimTurnoPreto = false;
    while(fimTurnoPreto == false)
    {
        pecaOrigem:
        cout << "Pecas pretas, escolha uma peca para movimentar.\n";
        cout << "Digite a linha da peca.\n";
        cin >> l;
        cout << "Digite a coluna da peca.\n";
        cin >> c;
        //Selecao da linha/coluna de origem
        while((tabuleiro[l][c] != 'P'))
        {//Enquato a peca de origem nao for selecionada corretamente
            cout << "Nao ha pecas pretas na linha na linha/coluna selecionados.\n";
            cout << "\n";
            goto pecaOrigem;
        }
        while ((tabuleiro[l][c] == 'P'))
        {//Selecao da linha coluna de destino
            pecaDestino:
            cout << "Pecas pretas, escolha um espaco para movimentar esta peca.\n";
            cout << "Digite a linha de destino.\n";
            cin >> linhaDestino;
            cout << "Digite a coluna de destino." << endl;
            cin >> colunaDestino;
            if((tabuleiro[l-1][c+1] == '_') && ( abs(l-linhaDestino)==1) && (abs(c-colunaDestino)==1))
            {
                tabuleiro[l-1][c+1] = 'P';
                tabuleiro[l][c] = '_';
                goto fimDoTurnoPreto;
            }
            else if ((tabuleiro[l-1][c-1] == '_') && ( abs(l-linhaDestino)==1) && (abs(c-colunaDestino)==1) )
            {
                tabuleiro[l-1][c-1] == 'P';
                tabuleiro[l][c] = '_';
                goto fimDoTurnoPreto;
            }
            else if(linhaDestino > 7)
            {// peca movendo na direcao inversa
                cout << "Movimento não permitido.\n";
                l=0;
                c=0;
                goto pecaOrigem;
            }
            else if (( abs(l-linhaDestino)!=1) && (abs(c-colunaDestino)!=1))
            {
                cout << "Movimento não permitido.\n";
                cout << "Os movimentos devem ser realizados na digonal.\n";
                l=0;
                c=0;
                goto pecaDestino;
            }
            else if (linhaDestino == l && ( abs(l-linhaDestino)==1) && (abs(c-colunaDestino)==1))
            {//peca movida fora da diagonal
                cout << "Movimento não permitido.\n";
                cout << "Os movimentos devem ser realizados na digonal.\n";
                l=0;
                c=0;
                goto pecaDestino;
            }
            else if ((colunaDestino == c) && ( abs(l-linhaDestino)==1) && (abs(c-colunaDestino)==1))
            {//peca movida fora da diagonal
                cout << "Movimento não permitido.\n";
                cout << "Os movimentos devem ser realizados na digonal.\n";
                l=0;
                c=0;
                goto pecaDestino;
            }
            else if((tabuleiro[l-1][c+1] == 'P'))
            {//peca nao pode ser movida pois existe outra peca no local
                cout << "Esta peca nao pode ser movida.\n";
                l=0;
                c=0;
                goto pecaOrigem;
            }
            else if ((tabuleiro[l-1][c-1] == 'P'))
            {
                cout << "Esta peca nao pode ser movida.\n";
                l=0;
                c=0;
                goto pecaOrigem;
            }
            else if ((tabuleiro[l-1][c+1] == 'B') && (tabuleiro[l-2][c+2] == '_') && ( abs(l-linhaDestino)==2) && (abs(c-colunaDestino)==2))
            {//comer a peca adversaria
                tabuleiro[l+2][c+2] = 'P';
                tabuleiro[l+1][c+1] = '_';
                tabuleiro[l][c] = '_';
                break;
            }
            else if ((tabuleiro[l-1][c-1] == 'B') && (tabuleiro[l-2][c-2] == '_') && ( abs(l-linhaDestino)==2) && (abs(c-colunaDestino)==2))
            {//comer a peca adversaria
                tabuleiro[l-2][c-2] = 'P';
                tabuleiro[l-1][c-1] = '_';
                tabuleiro[l][c] = '_';
                break;
            }
            else if ((tabuleiro[l-1][c+1] == 'B') && (tabuleiro[l-2][c+2] != '_'))
            {//peça não pode ser comida pois não há espaços vazios atrás dela
                cout << "Movimento invalido.\n";
                cout << "Esta peca nao pode ser comida pois nao ha espaços vazios atras dela.\n";
                goto pecaDestino;
            }
            else if ((tabuleiro[l-1][c-1] == 'B') && (tabuleiro[l-2][c-2] != '_'))
            {
                cout << "Movimento invalido.\n";
                cout << "Esta peca nao pode ser comida pois nao ha espaços vazios atras dela.\n";
                goto pecaDestino;
            }
        }
    fimDoTurnoPreto:
    fimTurnoPreto == true;
    fimTabuleiro();
    vencedor(tabuleiro);
    jogadorBranco(tabuleiro);
    }
}
int main()
{
    std::cout <<  " Bem vindo ao jogo de damas!\n" << std::endl;
    while(1) //Sorteia quem será o primeiro a jogar
    {
        loop1:
        std::cout <<  "Pecas brancas, digite um numero de 0 a 9 " << std::endl;
        std::cin >> numB;
        std::cout << "Pecas pretas digite um numero de 0 a 9 " << std::endl;
        std::cin >> numP;
        loop2:
        srand((int)time(NULL));
        numAleatorio = (rand()%9);
        valorB = abs (numB - numAleatorio); //valorBranco é o numero que ele escolheu em modulo menos o modulo do numero aleatorio
        valorP = abs (numP - numAleatorio);

        while(valorB == valorP)
        {
            srand(time(NULL));
            numAleatorio = (rand()%9);
            valorB = abs (numB - numAleatorio);
            valorP = abs (numP - numAleatorio);
        }
        if((numB>9)||(numB<0) || (numP>9)||(numP<0))
        {
            std::cout << "Valores invalidos, comece o jogo novamete!" << std::endl;
            goto loop1;
        }
        else if(numB == numP)
        {
            std::cout << "Empate! Jogue novamete!" << std::endl;
            goto loop1;
        }
        else if(valorB<valorP) //|| (numB>numP)
        {
            std::cout << "O numero sorteado foi " << numAleatorio << std::endl;
            std::cout << "Brancas comecam!\n" << std::endl;
            jogadorBranco(tabuleiro);
            //cout << "\n";
            //break;
        }
        else if(valorP<valorB) //|| (numB<numP)
        {
            std::cout << "O numero sorteado foi " << numAleatorio << std::endl;
            std::cout << "Pretas comecam!\n" << std::endl;
            jogadorPreto(tabuleiro);
            //cout << "\n";
            //break;
        }
    }
    return 0;
}
