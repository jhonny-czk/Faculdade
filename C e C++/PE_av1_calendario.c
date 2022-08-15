///Programacao Estruturada
///Avaliacao 01: Calendario em C
//Calendário mensal imprimível para qualquer mês e ano.
//Printable monthly calendar for any month and year.
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int descobreDiaDaSemana(int inputMes, int inputAno);
int quantDiaMes(int inputMes, int inputAno);
int formatacaoMes(int inputMes);
void printMes(int inputMes);

int main()
{
    int inputMes,inputAno;
    int dia,primeiroDiadoMes,quantidadeDiaMes;
    int i,formatacaoSemana=0;
    int espacos;
    //printf("Digite o mes e ano que deseja consultar\n");
    scanf("%d",&inputMes);
    scanf("%d",&inputAno);

    primeiroDiadoMes=descobreDiaDaSemana(inputMes,inputAno); //Chama a funcao p/ saber em que dia começa
                                                            //o mes eatribui o valor a variavel 'primeiroDiadoMes'
    quantidadeDiaMes=quantDiaMes(inputMes,inputAno); //Chama a funcao p/ saber qntos dias ha no mes selecionado


    espacos = formatacaoMes(inputMes);  //Atribui o valor do retorno da funcao 'formatacao mes a uma variavel.
    for(int k = espacos; k > 0; k--)    //O nome do mes deve estar centralizado. Essa eh oq o 'espacos' e 'for(k...) fazem
    {
        printf(" ");
    }
    printMes(inputMes); //Chama a funcao p/ printar o mes selecionado

    printf(" %04d\n", inputAno);
    printf(" S  T  Q  Q  S  S  D\n");
    //printf("%d\n",primeiroDiadoMes);
    dia=1;
    for(i=1;i<=7;i++)
    {
        if((primeiroDiadoMes==0)&&(quantidadeDiaMes=31)){
            printf("                   1\n");
            printf(" 2  3  4  5  6  7  8\n");
            printf(" 9 10 11 12 13 14 15\n");
            printf("16 17 18 19 20 21 22\n");
            printf("23 24 25 26 27 28 29\n");
            printf("30 31");
            return 0;
        }
            else if ((primeiroDiadoMes==0)&&(quantidadeDiaMes=30)){
                printf("                   1\n");
                printf(" 2  3  4  5  6  7  8\n");
                printf(" 9 10 11 12 13 14 15\n");
                printf("16 17 18 19 20 21 22\n");
                printf("23 24 25 26 27 28 29\n");
                printf("30");
                return 0;
            }
        if(i>=primeiroDiadoMes){
            printf("%2d ",dia);
            dia++;
        }
            else{
                printf("   ");
            }
    }
    printf("\n");
    for(i=dia; dia<=quantidadeDiaMes;dia++)//for(i=1; dia<=quantidadeDiaMes;dia++)
    {
        printf("%2d ",dia); //Printa o dia do mes

        formatacaoSemana=formatacaoSemana+1;

        if(formatacaoSemana>6)
        {
            printf("\n");       //A variavel 'formatacaoSemana' serve para encaixar o dia do mes
            formatacaoSemana=0; //na linha abaixo, auxiliando a formatacao do calendario
        }
    }

    return EXIT_SUCCESS;
}

int descobreDiaDaSemana(int inputMes, int inputAno)
{//Funcao p descobrir qual eh o dia da semana do 1º do mes selecionado.
    int a,b,c,d,dia,r;
    dia = 1;
    a = (14 - inputMes)/12;
    b = inputAno - a;
    c = inputMes + 12*a -2;
    d = dia+((31*c)/12)+b+(b/4)-(b/100)+(b/400);
    //r = (d % 7)+1;
    //r = ((d-2) % 7)+1;
    r = (d % 7);
                     //O dia da semana é um valor de 1 a 7
                     //Sendo q 1 representa o 1º dia da semana
    return r;
}

int quantDiaMes(int inputMes,int inputAno)
{//Funcao que diz quantos dias ha no mes selecionado
    int quantidadeDiaMes;

    if(inputMes==4 || inputMes==6 || inputMes==9 || inputMes==11){
        quantidadeDiaMes=30;
    }
        else if(inputMes==1 || inputMes==3 || inputMes==5 || inputMes==7 || inputMes==8 || inputMes==9 || inputMes==12){
            quantidadeDiaMes=31;
        }
            else if((inputMes==2)&&(inputAno % 400==0)) {
                quantidadeDiaMes=29; //Verifica se o ano eh bissexto
            }
                else if((inputAno % 4==0 && inputAno % 100!=0 )){
                    quantidadeDiaMes=29;
                }
                    else if(inputMes==2){
                        quantidadeDiaMes=28;
                    }
    return quantidadeDiaMes;
}

int formatacaoMes(int inputMes) //Funcao que conta quantas letras existem no nome do mes + ano "Marco 2020"
{                               //e devolve o quantidade de letras para que seja formatado o espaco correto com um 'for'.
    int quantidadeLetras;
    if(inputMes==1) {
        quantidadeLetras = 7;
    }
        else if(inputMes==2) {
        quantidadeLetras = 9;
        }
            else if( inputMes==3 || inputMes==4 || inputMes==6 || inputMes==7) {
            quantidadeLetras = 5;
            }
                else if(inputMes==5) {
                quantidadeLetras = 4;
                }
                    else if(inputMes==8) {
                    quantidadeLetras = 6;
                    }
                        else if(inputMes==9 || inputMes==11 || inputMes==12) {
                        quantidadeLetras = 8;
                        }
                            else if(inputMes==10) {
                            quantidadeLetras = 7;
                            }

    quantidadeLetras = (20 - (quantidadeLetras+5))/2;

    return quantidadeLetras;
}

void printMes(int inputMes) //Funcao que printa o nome do mes selecionado
{
    switch(inputMes)
    {
        case(1):
            printf("Janeiro");
        break;

        case(2):
            printf("Fevereiro");
        break;

        case(3):
            printf("Marco");
        break;

        case(4):
            printf("Abril");
        break;

        case(5):
            printf("Maio");
        break;

        case(6):
            printf("Junho");
        break;

        case(7):
            printf("Julho");
        break;

        case(8):
            printf("Agosto");
        break;

        case(9):
            printf("Setembro");
        break;

        case(10):
            printf("Outubro");
        break;

        case(11):
            printf("Novembro");
        break;

        case(12):
            printf("Dezembro");
        break;
    }
}
