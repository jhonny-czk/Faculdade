//Exemplo de implementação de uma fila (arquivo cabeçalho)
//Example of implementing a queue (header file)
#ifndef QUEUE_H
#define QUEUE_H

//Definicao abstrata do tipo QUEUE (fila)
struct Queue_;
typedef struct Queue_ Queue;

//include da stdlib para poder usar o size_t
#include <stdlib.h> 
#include <stdbool.h>

//Operacoes do TAD queue
Queue* create(size_t max_elements);
void destroy(Queue* queue);

bool enqueue(Queue* queue, int element); //fila de numeros int
int dequeue(Queue* queue); 
int front(const Queue* queue); //consulta do numero q está no inicio da fila
size_t size(const Queue* queue); 
bool underflow(const Queue* queue);
void print(const Queue* queue);

#endif //QUEUE_H
