#include <stdio.h>
#include <stdlib.h>
/*  init
 *  insert
 *  empty
 */
typedef struct triang{
    int c1;
    int c2;
    struct triang *prox;
} triang;

typedef struct triang *lista;

void initList(lista *prt)
{
    *prt = NULL;
}

void addNew(lista *prt, int c1, int c2)
{
    lista p, ax;
    ax = (triang *) malloc(sizeof(triang));
    ax->c1 = c1;
    ax->c2 = c2;
    p = *prt;
    ax->prox = p;
    *prt = ax;
}

void empty(lista *ptr) {
	lista t, p = *ptr;
	while (p) {
		t = p;
		p = p->prox;
		free(t);
	}
	*ptr = NULL;
}

void imprtList(lista *prt)
{
    lista p;
    for(p = *prt; p; p = p->prox)
    {
        printf("c1 = %d e c2 = %d\n", p->c1, p->c2);
    }
}

int main()
{
    int a, b;
    lista prt;
    initList(&prt);
    do
    {
        scanf("%d%d", &a, &b);
        addNew(&prt, a, b);
    }while(a > 0 && b > 0);
    imprtList(&prt);
    empty(&prt);
    return 0;
}
