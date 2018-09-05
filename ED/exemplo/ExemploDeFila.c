#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    int x;
    struct elemento *prox;
    struct elemento *ant;
}elemento;

typedef struct elemento *Pilha;

void iniciaPinha(Pilha *p){
    *p = NULL;
}

void addNewElemento(Pilha *p, Pilha *rabo, int a){
    Pilha ax, t = *p;
    ax = (elemento *) malloc(sizeof(elemento));
    ax->ant = NULL;
    ax->x = a;
    if(!(*p)){
        ax->prox = NULL;
        *rabo = ax;
        *p = ax;
    }
    else{
        t->ant = ax;
        ax->prox = t;
        *p = ax;
    }
}

void removeElemento(Pilha *rabo){
    Pilha ax = (*rabo)->ant;
    if(ax){
        *rabo = (*rabo)->ant;
        (*rabo)->prox = NULL;
    }
}

void liberaPilha(Pilha *p){
    Pilha t = *p, ax;
    while(t){
        ax = t;
        t = t->prox;
        free(ax);
    }
    free(*p);
}

void imprimePilha(Pilha *p){
    Pilha ax, t = *p;
    if(!t){
        printf("Lista vazia");
        return;
    }
    while(t){
        ax = t;
        t = t->prox;
        printf("%d ", ax->x);
    }
    printf("\n");
}

void faz(int n) {
    int i;
    Pilha P, rabo;
    iniciaPinha(&P);
    iniciaPinha(&rabo);
    for(i = 0; i < n; i++)
        addNewElemento(&P, &rabo, i+1);
    n--;
    printf("Discarded cards:");
    while(--n){
        printf(" %d,", rabo->x);
        removeElemento(&rabo);
        addNewElemento(&P, &rabo, rabo->x);
        removeElemento(&rabo);
    }
    printf(" %d", rabo->x);
    removeElemento(&rabo);
    addNewElemento(&P, &rabo, rabo->x);
    removeElemento(&rabo);
    printf("\nRemaining card: %d\n", P->x);
}

int main(){
    int n;
    while(scanf("%d", &n) && n){
        if(n > 1)
            faz(n);
        else
            printf("Discarded cards:\nRemaining card: 1\n");
    }
    return 0;
}
