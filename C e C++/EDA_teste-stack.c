//Exemplo de implementação de uma pilha 
//Example of a stack implementation 
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define MAX 100

int main(void)
{
    Stack* pilha = create(MAX);

    int contador = 0;
    char entrada[MAX];
    do
    {
        printf("Digite uma nova string para teste ou enter para terminar");
        __fpurge(stdin);
        gets(entrada);
        if(strlen(entrada) > 0){
            if (!push(pilha, entrada)){
                puts("ERRO NO EMPILHAMENTO");
                break;
            }
        }

    } while (strlen(entrada) > 0 && contador < MAX);

    puts("Conteudo da pilha agora: ");
    print(pilha);

    printf("A string do topo da pilha eh %s\n", top(pilha));

    free(pop(pilha));
    printf("Agora o topo eh %s\n", top(pilha));

    destroy(pilha);//nao esquecer de remover o objeto da memoria

    return EXIT_SUCCESS;
}
