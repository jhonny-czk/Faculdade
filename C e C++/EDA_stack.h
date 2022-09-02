//Exemplo de implementação de uma pilha (arquivo cabeçalho)
//Example of a stack implementation (header file)
#ifndef STACK_H
#define STACK_H

//Definicao abstrata do tipo STACK (pilha)
struct Stack_;
typedef struct Stack_ Stack;

//include stdlib para poder usar o size_t
#include <stdlib.h> 
#include <stdbool.h>

//Operacoes do TAD stack
Stack* create(size_t max_elements);
void destroy(Stack* stack);
bool push(Stack* stack, const char* element); //pilha de strings
char* pop(Stack* stack); // deve chamar free() para a string retornar apos o uso
const char* top(const Stack* stack); //consulta somente-leitura da string q está no topo da pilha
size_t size(const Stack* stack); 
bool underflow(const Stack* stack);
void print(const Stack* stack);

#endif //STACK_H
