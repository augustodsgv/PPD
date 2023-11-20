// Abordagem de de criar um thread para cada linha de A e C
// A ideia aqui é que sejam criadas menos threads, além de passar para
// as funções das threads somente a memória necessária para eles desempenharem suas funções
// Isso garante menos caches misses, além de gastar menos recursos com threads


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

typedef struct args{
    float * matA;
    float ** matB;
    float * matC;
    int matSize;
}args;

float ** povoaMatriz(int matSize){
    float ** mat = malloc(sizeof(float *) * matSize);
    for(int i = 0; i < matSize; i++) mat[i] = malloc(sizeof(float) * matSize);
    srand(time(NULL));
    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j++){
            mat[i][j] = ((float)rand() / (float)rand());
        }
    }
    return mat;
}

float ** povoaMatrizZero(int matSize){
    float ** mat = malloc(sizeof(float *) * matSize);
    for(int i = 0; i < matSize; i++) mat[i] = calloc(matSize, sizeof(float));

    return mat;
}

void printaMAtrix(float ** mat, int matSize){
    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j++){
            printf("%4.4f ", mat[i][j]);
        }
        printf("\n");
    }
}

void matrixMult(float ** matA, float ** matB, float ** matC, int matSize){
    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j++){
            for(int k = 0; k < matSize; k++){
                matC[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

void * MMThread(void * argumentos){
    float * matA = ((args*)argumentos)->matA;       // Conversão de ponteiro void para ponteiro de args
    float ** matB = ((args*)argumentos)->matB;      
    float * matC = ((args*)argumentos)->matC;
    int matSize = ((args*)argumentos)->matSize;

    for(int j = 0; j < matSize; j++){
        for(int k = 0; k < matSize; k++)
            matC[j] += matA[k] * matB[k][j];
    }
}

void MM(float ** matA, float ** matB, float ** matC, int matSize){
    pthread_t threads[matSize];

    for(int i = 0; i < matSize; i++){
        args * argumentos = malloc(sizeof(args));
        argumentos->matA = matA[i];
        argumentos->matB = matB;
        argumentos->matC = matC[i];
        argumentos->matSize = matSize;
        pthread_create(&threads[i], NULL, MMThread, argumentos);
        
    }
}

int main(int argc, char const * argv[]){
    int sizeOfMatriz = 3;

    if (argc > 1){
        sizeOfMatriz = strtol(argv[1], NULL, 10);
    }
    
    float ** matA = povoaMatriz(sizeOfMatriz);
    float ** matB = povoaMatriz(sizeOfMatriz);
    

    float ** matC = povoaMatrizZero(sizeOfMatriz);

    MM(matA, matB, matC, sizeOfMatriz);

    // printaMAtrix(matC, sizeOfMatriz);


    return 0;
}

