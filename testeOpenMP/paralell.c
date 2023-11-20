#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <unistd.h>

#define nIteracoes 10

int main(){
    // testando o comportamento normal
    int inicio, fim;
    // inicio = time(NULL);
    for(int i = 0; i < nIteracoes; i++){
        sleep(1);
    }

    // fim = time(NULL);
    // printf("tempo decorrido: %d\n", fim - inicio);


    return 0;
}