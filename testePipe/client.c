#include <stdio.h>

char intToChar(int entrada){
    return (char)(97 + entrada);
}

int main(){
    for(int i = 0; i < 26; i++){
        char entrada;
        scanf("%c", &entrada);
        printf("Cliente: Recebi %c\n", entrada);
    }

    for(int i = 0; i < 26; i++){
        printf("%c", intToChar(i));
    }

    return 0;
}