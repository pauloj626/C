#include <stdio.h>
#include <stdlib.h>

typedef struct pilha{
    char a;
    struct pilha *prox;
}pilha;

typedef struct pilha *lista;

void iniList(lista *p){
    *p = NULL;
}

void addNewElemento(lista *p, char a){
    lista pr = NULL, ax, t = *p;
    ax = (pilha *) malloc(sizeof(pilha));
    ax->a = a;
    if(!t){
        ax->prox = NULL;
        *p = ax;
        return;
    }
    ax->prox = t;
    (*p) = ax;
}

int removeElemento(lista *p){
    if(*p){
        *p = (*p)->prox;
        return 1;
    }
    return 0;
}

void limpaLista(lista *p){
    lista ax, axp = *p;
    while(axp){
        ax = axp;
        axp = axp->prox;
        free(ax);
    }
    *p = NULL;
}

void imprimeLista(lista *p){
    lista ax, t = *p;
    if(!t)
        printf("Lista vazia");
    while(t){
        ax = t;
        t = t->prox;
        printf("%c, ", ax->a);
    }
    printf("\n");
}

int main(){
    int n, s = 0;
    lista L;
    char ch;
    iniList(&L);
    scanf("%d", &n); getchar();
    while(n--){
        while((ch = getchar()) != '\n'){
            if(ch == '<')
                addNewElemento(&L, ch);
            else if(ch == '>')
                s += removeElemento(&L);
        }
        printf("%d\n", s);
        limpaLista(&L);
        s = 0;
    }
}
