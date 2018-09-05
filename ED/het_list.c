#include <stdio.h>
#include <stdlib.h>

typedef struct hnode {
    void *ptr;
    struct hnode *prox;
} hnode;

typedef struct hnode *hlist;

void insertData(hlist *,void *);
void emptyData(hlist *);
void printExample(hlist);
hlist buildExample();

int main(void) {
    hlist lst = buildExample();
    printExample(lst);
    emptyData(&lst);
    return 0;
}

hlist buildExample() {
    int i,j;
    do {
        printf("N (3 - 11): ");
        scanf("%d%*c",&i);
    } while (i < 3 || i > 11);
    hlist lst = NULL;
    char *datas;
    int *datai;
    for (j = 0; j < i; j++) {
        if (j % 2) {
            datas = (char *) malloc(50*sizeof(char));
            if (!datas) {
                puts("String not allocated.");
                exit(1);
            }
            printf("$: ");
            scanf(" %[^\n]",datas);
            insertData(&lst,datas);
        }
        else {
            datai = (int *) malloc(sizeof(int));
            if (!datai) {
                puts("Integer not allocated.");
                exit(1);
            }
            printf("#: ");
            scanf("%d%*c",datai);
            insertData(&lst,datai);
        }
    }
    return lst;
}

void insertData(hlist *ptr,void *data) {
    hlist n,a = NULL, p = *ptr;
    while(p) {
        a = p;
        p = p->prox;
    }
    n = (hnode *) malloc(sizeof(hnode));
    if (!data || !n) {
        puts("Data not allocated.");
        return;
    }
    n->ptr = data;
    if (!a) {
        n->prox = *ptr;
        *ptr = n;
    }
    else {
        n->prox = a->prox;
        a->prox = n;
    }   
}

void emptyData(hlist *ptr) {
    hlist t;
    while (*ptr) {
        t = *ptr;
        *ptr = (*ptr)->prox;
        free(t->ptr);
        free(t);
    }
    *ptr = NULL;
}

void printExample(hlist ptr) {
    int i;
    printf("$");
    for (i = 0; ptr; i++, ptr = ptr->prox) {
        if(i % 2) printf(" %s",(char *) (ptr->ptr));
        else printf(" %d",*(int *)(ptr->ptr));
    }
    puts("\n");
}
