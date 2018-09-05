#include <stdio.h>
#include <stdlib.h>

typedef struct num{
    int x;
    struct num *prox;
}listaNum;

//typedef struct num *listaNum;

void iniciarLista(listaNum **prt)
{
    *prt = NULL;
}

void inserirNum(listaNum **p, int x)
{
    listaNum *ax, *ant = NULL, *ax2;
    ax = (listaNum*) malloc(sizeof(listaNum));
    ax->prox=NULL;
    ax->x = x;
    if(!(*p))
    {
        printf("a lista e vazia\n");
        *p=(listaNum*)malloc(sizeof(listaNum));
        **p = *ax;
    }
    else
    {
        printf("a lista nao e vazia\n");
        ax2=(*p);
        while(ax2 && (x >= ax2->x))
        {
            ant = ax2;
            ax2 = ax2->prox;
        }
        ax->prox = ax2;
        ant->prox = ax;
        if(!(*p))
            printf("Eita\n");
    }
}

void imprimirLista(listaNum* prt)
{
    while(prt)
    {
        printf(" %d ", prt->x);
        prt = prt->prox;
    }
    printf("\n");
}

void limparLista(listaNum *prt)
{
    listaNum *a, *p = prt;
    while(p)
    {
        a = p;
        p = p->prox;
        free(a);
    }
    prt = NULL;
}

int main()
{
    int x;
    listaNum* prt;
    iniciarLista(&prt);
    while(scanf("%d", &x) && x > 0)
    {
        inserirNum(&prt, x);
    }
    imprimirLista(prt);
    limparLista(prt);
    return 0;
}
