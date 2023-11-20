#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função que calcúla o "meio" do vetor
int calcMeio(int inicio, int fim){
    return ceil((inicio + fim + 1) / 2);
}

// O objetivo aqui é juntar dois subvetores de forma ordenada.
// Vamos tratar aqui um vetor contínuo

// ini            mei         fim
//  0  1  2  3  4  5  6  7  8  9
// [1, 3, 5, 7, 9, 0, 2, 4, 8, 10]
void intercala(int * vetor, int ini, int fim){            // meio é indicado pelo último elemento do primeiro vetor
    int meio = calcMeio(ini, fim);
    int * vetorAux = (int*)malloc(sizeof(int) * (fim - ini + 1));
    int auxIndex = 0;
    int inicioReal = ini;
    int meioReal = meio;
    while(ini < meioReal && meio <= fim){
        if (vetor[ini] < vetor[meio]){
            vetorAux[auxIndex++] = vetor[ini++];
        }else{
            vetorAux[auxIndex++] = vetor[meio++];
        }
    }

    // Completando com os itens restantes
    while(ini < meioReal) vetorAux[auxIndex++] = vetor[ini++];
        
    while(meio <= fim) vetorAux[auxIndex++] = vetor[meio++];

    // Passando os valores do vetor auxiliar para o vetor original
    for (int i = 0; i < fim - inicioReal + 1; i++)
        vetor[inicioReal + i] = vetorAux[i];

    free(vetorAux);
}

// Função recursiva que realiza o merge sort
void mergeSortRec(int * vetor, int ini, int fim){     
    if (ini == fim) return;     // Caso base da recurção
    int meio = calcMeio(ini, fim);
    
    // Divisão
    mergeSortRec(vetor, ini, meio - 1);         // Primeira metade do vetor, indo do inicio até um termo antes do "meio"
    mergeSortRec(vetor, meio, fim);             // Segunda metade do vetor, indo da metade ao fim

    // Intercalação
    intercala(vetor, ini, fim);
}

// Função encapsulada que requer somente o tamanho do vetor
void mergeSort(int * vetor, int arraySize){
    mergeSortRec(vetor, 0, arraySize - 1);
}

void printaVetor(int * vetor, int size){
    for (int i = 0; i < size; i++)
        printf("%d ",vetor[i]);
    printf("\n");
}

int main(){
    int vetor[] = {0, 1123123, 33, 1, 88, 99, 808, 505};
    mergeSort(vetor, 8);
    printaVetor(vetor, 8);




    return 0;
}