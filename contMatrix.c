#include <stdio.h>
#include <stdlib.h>

#define size 10

int main(){
    // Matriz comum
    int ** matrizComum = (int **)malloc(sizeof(int*) * size);
    for(int i = 0; i < size; i++)   matrizComum[i] = (int*)malloc(sizeof(int) * size);

    int * matrizLinear = (int * )malloc(sizeof(int) * size * size);


    return 0;
}