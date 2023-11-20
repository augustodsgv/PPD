#include <stdio.h>
#include <stdlib.h>

#define size 1000000

int main(){
    int ** array = (int**)malloc(sizeof(int*) * size);    
    for(int i = 0; i < size; i++)   array[i] = (int*)malloc(sizeof(int) * size);
    

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            array[i][j] = i * j;
    
    /*
    FILE * arquivo = fopen("arquivo.txt", "w");


    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++){
            fwrite("0 ", sizeof(int) * 2, 1, arquivo);
        }
        fwrite("\n", sizeof(char), 1, arquivo);
    fclose(arquivo);
    

    
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            printf("%d ", array[i][j]);
        printf("\n");
    */
    printf("foi\n");

    return 0;
}