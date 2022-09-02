//Exemplo de implementação de uma pilha
//Example of a stack implementation 
#include <stdio.h>
#include "stack.h"

struct stack_ //Definicao concreta (implementacao) da pilha (da estrutura stack)
{
    char** vector; // (char*)* vector; <==> (é equivalente) char* vactor[]; (um vetor de ponteiros)
    size_t max_size;
    int stack_top; //indice do topo da pilha no vetor (fornece a contagem de forma indireta) 
};

Stack* create(size_t max_elements)
{
    Stack* new_stack = malloc(sizeof(Stack));
    new_stack->max_size = max_elements;
    new_stack->stack_top = -1; //nenhuma posicao do vetor ocupada ainda (nem a 0!)
    new_stack->vector = malloc(max_elements * sizeof(char*));
    return new_stack;
}

void destroy(Stack* stack)
{
    //precisa liberar a copia das strings alocadas dinamicamente na pilha
    int i;
    for(i=0; i<= stack->stack_top; i++)
    {
        free(stack->vector[i]);//libera memoria alocada por strdup()
    }
    free(stack->vector); //free na ordem inversa do q foi criado
    free(stack);
}


bool push(Stack* stack, const char* element) //pilha de strings
{
    if (stack->stack_top == stack->max_size -1) //vetor esta cheio?
    {
        return false;
    }
    char* copy = strdup(element);//duplicata alocada dinamicamente
    ++stack->stack_top;//avanca para a proxima posicao livre no vetor (novo topo)
    stack->vector[stack->stack_top] = copy;
    return true;
}

char* pop(Stack* stack) // deve chamar free() para a string retornar apos o uso
{
    if(!underflow(stack))
    {
        return NULL; //nao existe string a ser consultada
    }
    char* element = stack->vector[stack->stack_top];
    --stack->stack_top;
    return element;
}

const char* top(const Stack* stack) //consulta somente-leitura da string q está no topo da pilha
{
    if(underflow(stack))
    {
        return NULL; //nao ha string a ser consultada
    }
    return stack->vector[stack->stack_top];
}

size_t size(const Stack* stack)
{
    return stack->stack_top +1;
}

bool underflow(const Stack* stack)
{
    return stack->stack_top == -1;
}

void print(const Stack* stack)
{
    int i = stack->stack_top;
    while (i >= 0)
    {
        puts(stack->vector[i]);
        --i;
    }
}
