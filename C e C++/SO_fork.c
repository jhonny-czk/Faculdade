//Exemplo básico de Algoritmo Fork.
//Basic example of Fork Algorithm.
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    printf("--beginning of program\n");

    int counter = 0;
    pid_t pid = fork();
    //Fork cria um novo processo (filho) partindo de um processo existente (pai).

    if (pid == 0){
        // child process
        int i = 0;
        for (; i < 100; ++i)
        {
            printf("child process: counter=%d\n", ++counter);
            usleep(500);//usleep() Suspende a execução por 
            		//um intervalo de (pelo menos) x microssegundos.
        }
    }else if (pid > 0){
        // parent process
        int j = 0;
        for (; j < 100; ++j)
        {
            printf("parent process: counter=%d\n", ++counter);
            usleep(500);
        }
    }else{
        // fork failed
        printf("fork() failed!\n");
        return 1;
    }

    printf("--end of program--\n");

    return 0;
}
