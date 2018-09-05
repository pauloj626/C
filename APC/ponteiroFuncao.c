#include <stdio.h>

/* Retorna o dobro do valor dado. */
int dobra(int i) {
    return 2*i;
}

/* Retorna o valor absoluto do valor dado. */
int abs(int i) {
    return (i > 0)?i:(-i);
}

/* Substitui cada valor do vetor dado pelo resultado de
 * aplicar a fun��o dada a este valor.  */
void aplica(int (*comp)(int), int *v, int n) {
    int i;
    for(i = 0; i < n; v[i] = comp(v[i]), i++);
}

void mostra(int *vetor, int n) {
    int i;
    for(i = 0; i < n; ++i)
        printf("%d ", vetor[i]);
    printf("\n");
}

int main() {
    int vetor1[9] = {-1,-4,0,1,2,-2,3,-3,4};
    int vetor2[9] = {-1,-4,0,1,2,-2,3,-3,4};

    printf("Dobra:\n");
    aplica(dobra, vetor1, 9);
    mostra(vetor1, 9);

    printf("M�dulo:\n");
    aplica(abs, vetor2, 9);
    mostra(vetor2, 9);

    return 0;
}

/* Resultado esperado:
Dobra:
-2 -8 0 2 4 -4 6 -6 8
M�dulo:
1 4 0 1 2 2 3 3 4 */
