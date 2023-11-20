// Simulando uma multiplicação de matrizes transpostas.
// Esta é uma abordagem ingênua como a anterior, mas aqui simulamos
// que a multiplicaçao seja feita entre A e B^t. Isso ajuda pois nossas
// os elementos de B, que antes eram colunas, agora viram linhas, que são
// armezenadas de maneira contínua na memória. Isso não só evita que seja 
// necessário ficar consultando ponteiros continuamente, mas traz para o
// cache essa região

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

typedef struct args{
    float ** matA;
    float ** matB;
    float ** matC;
    int matSize;
    int i;
    int j;
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

/*
void MMThread(args argumentos){
    float ** matA = argumentos.matA;
    float ** matB = argumentos.matB;
    float ** matC = argumentos.matC;
    int matSize = argumentos.matSize;
    int line = argumentos.matSize;

    int somaParcial = 0;
    for(int j = 0; j < matSize; j++){
        for(int k = 0; k < matSize; k++){
            somaParcial += matA[line][k] * matB[k][j];
        }
    }
    return somaParcial;
}

void MatrixMult(float ** matA, float ** matB, float ** matC, int matSize){
    pthread_t threads[matSize];
    for(int i = 0; i < matSize; i++){
        args argumentos;
        argumentos.matA = matA;
        argumentos.matB = matB;
        argumentos.matC = matC;
        argumentos.matSize = matSize;
        argumentos.op = i;

        int status = pthread_create(&threads[i], NULL, MMThread, &argumentos);
    }
    for(int i =)


}

void MMThread2(args argumentos){
    float ** matA = argumentos.matA;
    float ** matB = argumentos.matB;
    float ** matC = argumentos.matC;
    int matSize = argumentos.matSize;
    int op = argumentos.op;

    int somaParcial = 0;
    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j++){
            matC[i][j] += matA[i][op] * matB[op][j];
        }
    }
    return somaParcial;
}

void MM2(float ** matA, float ** matB, float ** matC, int matSize){
    pthread_t threads[matSize];
    for(int i = 0; i < matSize; i++){
        args argumentos;
        argumentos.matA = matA;
        argumentos.matB = matB;
        argumentos.matC = matC;
        argumentos.matSize = matSize;
        argumentos.op = i;

        int status = pthread_create(&threads[i], NULL, MMThread, &argumentos);
    }
    for(int i =)


}
*/
void * MMThread(void * argumentos){
    float ** matA = ((args*)argumentos)->matA;
    float ** matB = ((args*)argumentos)->matB;
    float ** matC = ((args*)argumentos)->matC;
    int matSize = ((args*)argumentos)->matSize;
    int i = ((args*)argumentos)->i;
    int j = ((args*)argumentos)->j;

    for(int k = 0; k < matSize; k++){
        matC[i][j] += matA[i][k] * matB[j][k];
    }
}

void MM(float ** matA, float ** matB, float ** matC, int matSize){
    pthread_t threads[matSize][matSize];
    for(int i = 0; i < matSize; i++){
        for(int j = 0; j < matSize; j++){
            args * argumentos = malloc(sizeof(args));
            argumentos->matA = matA;
            argumentos->matB = matB;
            argumentos->matC = matC;
            argumentos->matSize = matSize;
            argumentos->i = i;
            argumentos->j = j;

            pthread_create(&threads[i][j], NULL, MMThread, argumentos);
        }
    }
}

int main(int argc, char const * argv[]){
    int sizeOfMatriz = 1000;

    if (argc > 1){
        sizeOfMatriz = argv[1];
    }

    float ** matA = povoaMatriz(sizeOfMatriz);
    float ** matB = povoaMatriz(sizeOfMatriz);
    

    float ** matC = povoaMatrizZero(sizeOfMatriz);

    MM(matA, matB, matC, sizeOfMatriz);

    // printaMAtrix(matC, sizeOfMatriz);


    return 0;
}