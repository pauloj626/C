/**      @file: 00-binario.c
 *     @author: Guilherme N. Ramos (gnramos@unb.br)
 * @disciplina: Algoritmos e Programa��o de Computadores
 *
 * Exemplo de leitura e escrita em arquivo bin�rio. */

#include <stdio.h>
#include <stdlib.h>

typedef char string[50];

/* Cria um arquivo com o nome dado como argumento. Retorna
 * EXIT_SUCCESS caso seja poss�vel, EXIT_FAILURE caso
 * contr�rio. */
int cria(char* arquivo) {
  const string str = "Algoritmos e Programa��o de Computadores";
  const double d = 12.23;
  const int i = 101;

  /* O que acontece se n�o for poss�vel abrir o arquivo? (ele
   * n�o existe, voc� n�o tem permiss�o para tanto, algu�m j�
   * o est� manipulando, etc.) */
  FILE *fp = fopen(arquivo, "wb+"); /* "b" de "bin�rio"... */

  /* � f�cil verificar: se for poss�vel abrir o arquivo, o
   * ponteiro indicar� um endere�o de mem�ria v�lido; se n�o
   * for poss�vel, basta indicar isso atribuindo ao ponteiro
   * um valor notoriamente "inv�lido": o endere�o 0 (NULL). */
  if((fp == NULL) && (!fp) && (fp == 0)) {
      /* Os testes s�o equivalentes. */
      printf("N�o foi poss�vel abrir \"%s\".\n", arquivo);
      return EXIT_FAILURE;
  }

  /* Escreve no arquivo na ordem: string -> real -> inteiro. */
  fwrite(str, sizeof(str), 1, fp);
  fwrite(&d, sizeof(d), 1, fp);
  fwrite(&i, sizeof(i), 1, fp);

  /* O programador � respons�vel pelo arquivo. */
  fclose(fp);

  return EXIT_SUCCESS;
}

/* Mostra na sa�da padr�o o conte�do do arquivo dado como argumento. */
void mostra(char* arquivo) {
  string str;
  double d;
  int i;
  FILE *fp = fopen(arquivo, "rb");

  if(!fp)
      return;

  /* L� do arquivo na ordem: string -> real -> inteiro. � essencial que seja
   * a mesma ordem em que foi escrito, pois as informa��es estar�o incorretas
   * caso contr�rio. */
  fread(str, sizeof(str), 1, fp); /* tem de ser do tamanho certo! */
  fread(&d, sizeof(d), 1, fp);
  fread(&i, sizeof(i), 1, fp);
  fclose(fp);

  printf("string = %s\n", str);
  printf("double = %lf\n", d);
  printf("   int = %d\n", i);
}

/* Mostra na sa�da padr�o o conte�do do arquivo dado como argumento, mas l� as
 * informa��es em ordem diferente da que foi escrita. */
void mostra_errado(char* arquivo) {
  string str;
  double d;
  int i;
  FILE *fp = fopen(arquivo, "rb");

  if(!fp)
      return;

  /* L� do arquivo na ordem: inteiro -> real -> string. */
  fread(&i, sizeof(i), 1, fp);
  fread(&d, sizeof(d), 1, fp);
  fread(str, sizeof(str), 1, fp); /* tem de ser do tamanho certo! */
  fclose(fp);

  printf("string = %s\n", str);
  printf("double = %lf\n", d);
  printf("   int = %d\n", i);
}

int main() {
  char arquivo[] = "apc.c.bin";

  if(cria(arquivo) == EXIT_SUCCESS) {
    printf("Leitura correta:\n");
    mostra(arquivo);
    printf("\nLeitura incorreta:\n");
    mostra_errado(arquivo);
  }

  return EXIT_SUCCESS;
}
