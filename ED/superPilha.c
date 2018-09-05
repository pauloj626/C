#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	void *valor;
	char type;
	struct Node *prox;
}Node;

typedef struct Node *Pilha;

Pilha  buildPilha ();
int    insertPilha(Pilha *, void *, char) ;
void  *getValue   (Pilha *, int   , char*);
void   printPilha (Pilha  );
void   removePilha(Pilha *);
void   emptyPilha (Pilha *);
void   printValue (void  *, char);

int main(int argv, char *args[]){
	char *s, *h, tipo;
	int *j;
	float *k;
	void *valor = NULL;
	Pilha P = buildPilha();
	
	s = (char *) malloc(50*sizeof(char));
	strcpy(s, "Ola Mundo");
	insertPilha(&P, (void *) s, 's');
	
	h = (char *) malloc(sizeof(char));
	*h = 'J';
	insertPilha(&P, (void *) h, 'c');

	j = (int *) malloc(sizeof(int));
	*j = 17;
	insertPilha(&P, (void *) j, 'i');

	k = (float *) malloc(sizeof(float));
	*k = 3.1415;
	insertPilha(&P, (void *) k, 'f');	

	s = (char *) malloc(50*sizeof(char));
	strcpy(s, "#Bolsonaro2018");
	insertPilha(&P, (void *) s, 's');
	
	valor = getValue(&P, 0, &tipo);

	printValue(valor, tipo);
	printf("\n");

	/*
	Descomente para imprimir a Pilha
	printf("Pilha:\n");
	printPilha(P);*/

	emptyPilha(&P);
	return 0;
}

Pilha buildPilha(){
	Pilha P = NULL;
	return P;
}

int insertPilha(Pilha *P, void *value, char type){
	Pilha ax;
	ax = (Node *) malloc(sizeof(Node));
	if(!ax){
		printf("Data not allocated.\n");
		return 0;
	}
	ax->valor = value;
	ax->prox = *P;
	ax->type = type;
	*P = ax;
	return 1;
}

void removePilha(Pilha *P){
	Pilha ax;
	if(!P){
		printf("Empty object\n");
		return;
	}
	ax = *P;
	*P = ax->prox;
	free(ax->valor);
	free(ax);
	ax = ax->valor = NULL;
}

void printValue(void *value, char type){ 
	switch(type){
		case 'i':
			printf("%d", *(int *) value);
			break;
		case 'c':
			printf("%c", *(char *) value);
			break;
		case 'f':
			printf("%f", *(float *) value);
			break;
		case 'd':
			printf("%lf", *(double *) value);
			break;
		case 's':
			printf("%s",   (char *) value);
			break;
		default:
			printf("You have to add this type\n");
	}
}

void printPilha(Pilha P){
	int i;
    for (i = 0; P; i++, P = P->prox) {
        printf("%d -> ", i);
        printValue(P->valor, P->type);
        printf(";\n");
    }
    if(i == 0)
    	printf("Pilha Vazia\n");
}

void *getValue(Pilha *P, int i, char *type){
	int j;
	Pilha ax = *P;
	for(j = 0; ax && i > j; j++, ax = ax->prox);
	if(!ax){
		printf("Out of index\n");
		return '\0';
	}
	*type = ax->type;
	return ax->valor;
}

void emptyPilha(Pilha *P){
	Pilha t;
    while(*P){
        t = *P;
        *P = (*P)->prox;
        free(t->valor);
        free(t);
        t = t->valor = NULL;
    }
    *P = NULL;
}