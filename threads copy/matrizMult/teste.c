#include <stdio.h>

int main(){
    int intervalo = 19783 / 8;
    int j = 0;
    for (int i = 0; i < 8; i++){
        printf("%d até %d\n", j, j + intervalo - 1);
        j += intervalo;
    }


    return 0;
}