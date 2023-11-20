// Abordagem trandicional na força bruta O(N³).
// Abordagem estúpida e que funciona relativamente bem por causa
// do compilador

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main(){
    int sizeOfMatriz = 1000;
    float ** matA = povoaMatriz(sizeOfMatriz);
    float ** matB = povoaMatriz(sizeOfMatriz);
    float ** matC = povoaMatrizZero(sizeOfMatriz);

    matrixMult(matA, matB, matC, sizeOfMatriz);

    // printaMAtrix(matC, sizeOfMatriz);


    return 0;
}