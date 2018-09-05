#include <stdio.h>
#include <stdlib.h>

typedef struct tipo{
    int  x;
    char c;
    struct tipo *prox;
}tipo;

typedef struct tipo *lista;

void iniList(lista *prt)
{
    *prt = NULL;
}

void addNewElemento(lista *prt, int x, char a)
{
    lista ant = NULL, ax, p = *prt;
    while(p)
    {
        ant = p;
        p = p->prox;
    }
    ax = (tipo *) malloc(sizeof(tipo));
    ax->x = x;
    ax->c = a;
    if(!ant)
    {
        ax ->prox = NULL;
        *prt = ax;
    }
    else
    {
        ant->prox = ax;
        ax->prox = p;
    }
}

void imprmiList(lista p)
{
    for(; p; p = p->prox)
    {
        printf("x = %d e c = %c\n", p->x, p->c);
    }
}

void limpaList(lista *prt)
{
    lista t, p = *prt;
    while(p)
    {
        t = p;
        p = p->prox;
        free(t);
    }
    *prt = NULL;
}

int main()
{
    int x;
    char a;
    lista prt;
    iniList(&prt);
    do
    {
        scanf("%d %c", &x, &a);
        addNewElemento(&prt, x, a);
    }while(x > 0);
    imprmiList(prt);
    limpaList(&prt);
    return 0;
}
