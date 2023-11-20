#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
    clock_t inicio, fim;
    inicio = clock();
    sleep(3);
    fim = clock();

    printf("time = %lf\n", (double)((fim - inicio) / CLOCKS_PER_SEC));
    printf("%d\n", CLOCKS_PER_SEC);

    return 0;
}