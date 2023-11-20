// Abordagem igual ao do thread3, mas agora fazendo a matriz B inversa.
// Vamos testar se o cache e os ponteiros fazem valer o tempo de inverter uma
// Matriz
// Para início, parece que não haver tanta vantagem, por que a linha do B precisa ficar mudando,
// entretanto deve ajudar na multiplicação dos elementos em si


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
    float ** matBt = ((args*)argumentos)->matB;      
    float * matC = ((args*)argumentos)->matC;
    int matSize = ((args*)argumentos)->matSize;

    for(int j = 0; j < matSize; j++){
        for(int k = 0; k < matSize; k++)
            matC[j] += matA[k] * matBt[j][k];
    }
}

void MM(float ** matA, float ** matB, float ** matC, int matSize){
    // Invertendo B
    float ** matBt = malloc(sizeof(float * ) * matSize);
    for (int i = 0; i < matSize; i++) matBt[i] = malloc(sizeof(float) * matSize);
    for(int i = 0; i < matSize; i++)
        for(int j = 0; j < matSize; j++)
            matBt[i][j] = matB[j][i];


    pthread_t threads[matSize];

    for(int i = 0; i < matSize; i++){
        args * argumentos = malloc(sizeof(args));
        argumentos->matA = matA[i];
        argumentos->matB = matBt;
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

