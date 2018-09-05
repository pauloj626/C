#include <stdio.h>
#include <stdlib.h>

void scanearVetor(int *v, int n){
    int i;
    for(i = 0; i < n; i++)
        scanf("%d", v+i);
}

void positivos(int *v, int n){
    int i;
    for(i = 0; i < n; i++)
        if(v[i] > 0)
            printf("%d ", v[i]);
    putchar('\n');
}

void menoresQue2(int *v, int n){
    int i;
    for(i = 0; i < n; i++)
        if(v[i] < 2)
            printf("%d ", v[i]);
    putchar('\n');
}

void osPares(int *v, int n){
    int i;
    for(i = 0; i < n; i++)
        if(v[i]%2 == 0)
            printf("%d ", v[i]);
    putchar('\n');
}

int main(){
    int v[10], i;
    void (*f[])(int *, int) = {scanearVetor, positivos, menoresQue2, osPares};
    for(i = 0; i < 4; i++)
        f[i](v, 10);
    return 0;
}
