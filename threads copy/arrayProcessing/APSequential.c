#include <stdio.h>
#include "hardProcess.h"
#include "matrixes.h"

void APSequential(long long matrizSize, long long matriz[matrizSize][matrizSize]){
    for(int i = 0; i < matrizSize; i++){
        for(int j = 0; j < matrizSize; j++){
            matriz[i][j] = hardProcess(matriz[i][j]);
        }
    }
}

int main(){
    APSequential(15, matrix_15_15);
    printaArray(15, matrix_15_15);

    return 0;
}