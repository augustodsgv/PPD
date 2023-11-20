#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));

    printf("%f\n", (float)rand() / rand());

    return 0;
}
/*
float ** matA = malloc(sizeof(float *) * 3);
    for (int i = 0; i < 3; i ++) matA[i] = malloc(sizeof(float) * 3);
    float ** matB = malloc(sizeof(float *) * 3);
    for (int i = 0; i < 3; i ++) matB[i] = malloc(sizeof(float) * 3);

    matA[0][0] = 2;
    matA[0][1] = 0;
    matA[0][2] = 1;
    matA[1][0] = 3;
    matA[1][1] = 0;
    matA[1][2] = 0;
    matA[2][0] = 5;
    matA[2][1] = 1;
    matA[2][2] = 1;

    matB[0][0] = 1;
    matB[0][1] = 0;
    matB[0][2] = 1;
    matB[1][0] = 1;
    matB[1][1] = 2;
    matB[1][2] = 1;
    matB[2][0] = 1;
    matB[2][1] = 1;
    matB[2][2] = 0;
    */