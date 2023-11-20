#include <stdio.h>
#include "hardProcess.h"

long long hardProcess(long long n){
    return fatorial(n);
}

long long  fatorial(long long n){
    if (n == 0)  return 1;
    return n * hardProcess(n - 1);
}

void printaDArray(int arraySize, long long ** matriz){
    for(int i = 0; i < arraySize; i++){
        for(int j = 0; j < arraySize; j++)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
}

void printaArray(int arraySize, long long matriz[arraySize][arraySize]){
    for(int i = 0; i < arraySize; i++){
        for(int j = 0; j < arraySize; j++)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
}

