#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define arraySize 100

int main() {
    // Semente para a função rand() baseada no tempo atual
    srand(time(NULL));

    // Definindo o tamanho da matriz
    int matriz[arraySize][arraySize];

    // Preenchendo a matriz com valores aleatórios
    for (int i = 0; i < arraySize; ++i) {
        for (int j = 0; j < arraySize; ++j) {
            matriz[i][j] = rand() % arraySize;  // Números aleatórios de 0 a 999
        }
    }

    // Imprimindo os primeiros elementos da matriz como exemplo
    for (int i = 0; i < arraySize; ++i) {
        printf("{");
        for (int j = 0; j < arraySize; ++j) {
            printf("%d, ", matriz[i][j]);
        }
        printf("},\n");
    }

    return 0;
}