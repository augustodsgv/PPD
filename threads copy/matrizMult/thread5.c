// Acompanhando a abordagem de dividir 1 thread para cada linha, vamos tentar
/*
limitar o número de threads ao número de cores do meu pc. 
Meu pc tem 4 núcleos e 8 threads (thread não no mesmo sentido de SO,
mas no sentido de harware). Para simplificar vamos chamar tudo de Core
A ideia é que há um custo em criar threads, então vamos criar um número 
fixo de threads e dividiro trabalho entre elas.
Uma preocupação aqui é com a divisão de linhas. Caso nLinhas não seja múltiplo de nCores
devemos passar essas tarefas "a mais" ou "a menos" para alguém.
Uma abordagem mais simples é dividir o número de threads pelo maior múltiplo 
do número de corese deixar o resto para uma das threads, já que tratamos aqui 
de um número pequeno de cores e o desbalanceamento será pequno. Entretanto caso estivessemos
falando de um processador com muito mais núcleos, isso poderia ser significativo
Outra abordagem seria dividir nLinhas / nCores - 1 e atribuir o resto das operações para
um último núcleo. Para casos com resto muito próximo do número de núcleos isso é uma solução
muito boa, entretanto para casos onde o resto é muito pequeno um core ficará muito desbalanceado.
Aos meus olhos parece que juntar as duas ideias é uma soluçao interessate, mas precisaria fazer
os cálculos sobre o limiar entre as duas.
Se bem que parando pra pensar, por mais que o número de cores de um sistema computacional cresça muito
o número de interações que ele terá que fazer será infinitamente maior que ele, então é muito provável
que um seja múltiplo do outro ou que essa diferença seja simplesmente despresível.
De toda forma é um exercício interessante de se pensar casa o problema seja enorme e não tao paralelizável assim
De toda forma, vou usar o primeeiro método no meu pq é mais fácil.
Uma questão a se pensar é como a matriz A e C serão passadas às threads. Nas etapas anteriores começamos a passar
somente um vetor de A e um de Ce não a matriz toda para cada thread. Isso não é possível agora, já que cada thread
vai ler mais de uma linha. talvez valha a pena alocar uma nova matriz
individual para cada uma com somente os elementos que a thread irá usar. Isso ficará para a próxima tentativa
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define N_CORES 3

typedef struct args{
    float ** matA;
    float ** matB;
    float ** matC;
    int matSize;
    int begin;
    int end;
}args;

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

void * MMThread(void * argumentos){
    float ** matA = ((args*)argumentos)->matA;       // Conversão de ponteiro void para ponteiro de args
    float ** matBt = ((args*)argumentos)->matB;      
    float ** matC = ((args*)argumentos)->matC;
    int matSize = ((args*)argumentos)->matSize;
    int begin = ((args*)argumentos)->begin;
    int end = ((args*)argumentos)->end;
    for(int i = begin; i < end; i++){
        for(int j = 0; j < matSize; j++){
            for(int k = 0; k < matSize; k++){
                printf("i: %d, j: %d, k: %d\n", i, j, k);
                matC[i][j] += matA[i][k] * matBt[j][k];
            }
        }
    }
}

void MM(float ** matA, float ** matB, float ** matC, int matSize){
    // Fazendo a transposta de B
    float ** matBt = malloc(sizeof(float * ) * matSize);
    for (int i = 0; i < matSize; i++) matBt[i] = malloc(sizeof(float) * matSize);
    for(int i = 0; i < matSize; i++)
        for(int j = 0; j < matSize; j++)
            matBt[i][j] = matB[j][i];

    pthread_t threads[N_CORES];
    int intervalo = matSize / N_CORES;
    int inicio = 0;
    for(int i = 0; i < N_CORES - 1; i++){       // -1 pois o último irá pegar o resto que sobrar
        args * argumentos = malloc(sizeof(args));
        argumentos->matA = matA;
        argumentos->matB = matBt;
        argumentos->matC = matC;
        argumentos->begin = inicio;
        argumentos->end = inicio + intervalo;        // -1 para sempre cortar para baixo
        argumentos->matSize = matSize;
        pthread_create(&threads[i], NULL, MMThread, argumentos);  
        inicio += intervalo;
    }

    // Tratamento do último core
    args * argumentos = malloc(sizeof(args));
    argumentos->matA = matA;
    argumentos->matB = matBt;
    argumentos->matC = matC;
    argumentos->begin = inicio;
    argumentos->end = matSize;              // O último pega o restante dos elementos até o final do array
    argumentos->matSize = matSize;
    pthread_create(&threads[matSize - 1], NULL, MMThread, argumentos);

}

int main(int argc, char const * argv[]){
    int sizeOfMatriz = 3;

    if (argc > 1){
        sizeOfMatriz = strtol(argv[1], NULL, 10);
    }
    
    float ** matA = povoaMatriz(sizeOfMatriz);
    float ** matB = povoaMatriz(sizeOfMatriz);
    

    float ** matC = povoaMatrizZero(sizeOfMatriz);

    MM(matA, matB, matC, sizeOfMatriz);

    // sleep(1);
    printaMAtrix(matC, sizeOfMatriz);


    return 0;
}
