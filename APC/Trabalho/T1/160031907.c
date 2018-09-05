/*		João Paulo Pinhiero Melo
 *			   16/0031907
 *Primeiro trabalho de APC, prof: Guilherme N. Ramos
 *			RPG dos vampiros
 *OBS: É quase inevitavel que o Jogo não apersentar
 *desequilibrio, tentei minimizar ao maximo.
 *Também gostaria de ressaltar que para o ataque
 *rapido e para a defesa no seu uso o usuario pode
 *ganhar HP, isso para não torna tais ataques
 *inuteis, dessa forma se você usar o ataque
 *rapido você ganhará HP e a mensagem que irá apare-
 *cer será: "'nome' usou atack rapido" e se você
 *usar a defesa e NÃO ser atacado você ganhará
 *HP e será imprimido a seguinte mensagem:
 *"'nome' ganhou HP".
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  CSI         "\x1B["
#define  BOLD_OFF    "21m"

/* Text colors */
#define  T_RED       "31m"
#define  T_YELLOW    "33m"
#define  T_BLUE      "34m"
#define  T_WHITE     "37m"
#define  T_PURPLE    "35m"

/* Background */
#define  B_RED       "41m"
#define  B_YELLOW    "43m"
#define  B_BLUE      "44m"
#define  B_DEFAULT   "49m"

typedef struct vampiro{
	char nome[20];
	int hpMax;
	int hp;
	int atack;
	int life_steal;
	int precisao;
	int num_porcoes;
	int porcoes_usadas;
	char atordoado;
}vampiro;

void limpaBuffer()
{
	char ch;
	while((ch =getchar()) != '\n');
}

void imprimeTitle()
{
	printf("%s%s  \t\t\t\t\t 	               __       __    ___   __%s%s\n", CSI, T_PURPLE, CSI, T_WHITE);
	printf("%s%s  \t\t\t\t\t   \\    /  /\\   |\\  /||  |  |  |  \\  |   | |%s%s\n", CSI, T_PURPLE, CSI, T_WHITE);
 	printf("%s%s  \t\t\t\t\t    \\  /  /__\\  | \\/ ||--'  |  |__|  |   | '--.%s%s\n", CSI, T_PURPLE, CSI, T_WHITE);
  	printf("%s%s  \t\t\t\t\t     \\/  /    \\ |    ||     |  |  \\  |___|  __|%s%s\n", CSI, T_PURPLE, CSI, T_WHITE);
}

void completaNome(char *nome)
{
	int i = 0;
	while(nome[i] != '\0')
		i++;
	if(i >= 7)
		return;
	while(i < 7)
	{
		nome[i] = ' ';
		i++;
	}
	nome[i] = '\0';
}

void iniciaPlayer(vampiro *player)
{
	char nome[20];
	printf("\n\n\n");
	imprimeTitle();
	printf("\n\n\t\t\t\t\t%s%sDigite o nome que deseja: ", CSI, T_RED);
	scanf("%7[^\n]", nome);
	printf("%s%s", CSI, T_WHITE);
	completaNome(nome);
	limpaBuffer();
	strcpy(player->nome, nome);
	player->hpMax = 60+rand()%41;
	player->hp = player->hpMax;
	player->atack = 5+rand()%6;
	player->life_steal = 5+rand()%6;
	player->precisao = 60+rand()%30;
	player->num_porcoes = 3+rand()%3;
	player->porcoes_usadas = 0;
	player->atordoado = 'N';
}

void restartPlayer(vampiro *player)
{
	player->hp = player->hpMax;
	player->porcoes_usadas = 0;
	player->atordoado = 'N';
}

void iniciaInimigo(vampiro *inimigo)
{
	int nivel = rand()%6;
	if(nivel < 4)
	{
		strcpy(inimigo->nome, "Inimigo");
		inimigo->hpMax = 60+rand()%41;
		inimigo->hp = inimigo->hpMax;
		inimigo->atack = 5+rand()%6;
		inimigo->life_steal = 5+rand()%4;
		inimigo->precisao = 60+rand()%21;
		inimigo->num_porcoes = 3+rand()%3;
	}
	else if(nivel == 4)
	{
		strcpy(inimigo->nome, "Alucard");
		inimigo->hpMax = 120;
		inimigo->hp = inimigo->hpMax;
		inimigo->atack = 15;
		inimigo->life_steal = 10;
		inimigo->precisao = 40;
		inimigo->num_porcoes = 2;
	}
	else
	{
		strcpy(inimigo->nome, "Dracula");
		inimigo->hpMax = 150;
		inimigo->hp = inimigo->hpMax;
		inimigo->atack = 20;
		inimigo->life_steal = 10;
		inimigo->precisao = 30;
		inimigo->num_porcoes = 1;
	}
	inimigo->porcoes_usadas = 0;
	inimigo->atordoado = 'N';
}

void restartInimigo(vampiro *inimigo)
{
	free(inimigo);
	inimigo = (vampiro *) malloc(sizeof(vampiro));
	iniciaInimigo(inimigo);
}

void barraDeVida(vampiro *vamp, int ehInimigo)
{
	int i;
	if(ehInimigo)
		printf("\t\t\t\t\t%s%s%s HP: ", CSI, T_RED,vamp->nome);
	else
		printf("\t\t\t\t\t%s%s%s HP: ", CSI, T_BLUE,vamp->nome);
	for(i = 0; i <= (vamp->hp)/5; i++)
	{
		if(vamp->hp > (3*(vamp->hpMax))/4)
			printf("%s%s %s%s", CSI, B_BLUE, CSI, B_DEFAULT);
		else if(vamp->hp > (vamp->hpMax)/4)
			printf("%s%s %s%s", CSI, B_YELLOW, CSI, B_DEFAULT);
		else
			printf("%s%s %s%s", CSI, B_RED, CSI, B_DEFAULT);
	}
	printf("\n\n%s%s", CSI, T_WHITE);
}

void imprVampiro(vampiro *player, vampiro *inimigo)
{
	imprimeTitle();
	printf("\n\n\n%s%s", CSI, T_PURPLE);
	printf("\t\t\t\t\t*\t%s%s    %s    %s%s\t | \t%s%s   %s   %s%s\t*\n", CSI, T_BLUE, player->nome, CSI, T_PURPLE, CSI, T_RED, inimigo->nome, CSI, T_PURPLE);
	printf("\t\t\t\t\t*\t%s%sHP = %.3d/%.3d%s%s\t | \t%s%sHP = %.3d/%.3d%s%s\t*\n",CSI, T_BLUE, player->hp, player->hpMax, CSI, T_PURPLE, CSI, T_RED, inimigo->hp, inimigo->hpMax, CSI, T_PURPLE);
	printf("\t\t\t\t\t*\t%s%sATACK  =  %.3d%s%s\t | \t%s%sATACK  =  %.3d%s%s\t*\n",CSI, T_BLUE, player->atack, CSI, T_PURPLE, CSI, T_RED, inimigo->atack, CSI, T_PURPLE);
	printf("\t\t\t\t\t*\t%s%sPORCOES= %d/%d%s%s\t | \t%s%sPORCOES= %d/%d%s%s\t*\n",CSI, T_BLUE, player->porcoes_usadas, player->num_porcoes, CSI, T_PURPLE, CSI, T_RED, inimigo->porcoes_usadas, inimigo->num_porcoes, CSI, T_PURPLE);
	printf("\t\t\t\t\t*\t%s%sPRECISAO=%.3d%s%s\t | \t%s%sPRECISAO=%3.d%s%s\t*\n",CSI, T_BLUE, player->precisao, CSI, T_PURPLE, CSI, T_RED, inimigo->precisao, CSI, T_PURPLE);
	printf("\t\t\t\t\t*\t%s%slifSteal= %.3d%s%s\t | \t%s%slifSteal= %3.d%s%s\t*\n",CSI, T_BLUE, player->life_steal, CSI, T_PURPLE, CSI, T_RED, inimigo->life_steal, CSI, T_PURPLE);
	if(player->atordoado == 'S' && inimigo->atordoado == 'S')
	{
		printf("\t\t\t\t\t*\t %s%s***********%s%s\t | \t %s%s***********%s%s\t*\n", CSI, T_YELLOW, CSI, T_PURPLE, CSI, T_YELLOW, CSI, T_PURPLE);
		printf("\t\t\t\t\t*\t %s%s*ATORDOADO*%s%s\t | \t %s%s*ATORDOADO*%s%s\t*\n", CSI, T_YELLOW, CSI, T_PURPLE, CSI, T_YELLOW, CSI, T_PURPLE);
		printf("\t\t\t\t\t*\t %s%s***********%s%s\t | \t %s%s***********%s%s\t*\n", CSI, T_YELLOW, CSI, T_PURPLE, CSI, T_YELLOW, CSI, T_PURPLE);
	}
	else if(player->atordoado == 'S')
	{
		printf("\t\t\t\t\t*\t%s%s ***********%s%s\t | \t%s%s ***********%s%s\t*\n", CSI, T_YELLOW, CSI, T_PURPLE, CSI, T_RED, CSI, T_PURPLE);
		printf("\t\t\t\t\t*\t%s%s *ATORDOADO*%s%s\t | \t%s%s ***********%s%s\t*\n", CSI, T_YELLOW, CSI, T_PURPLE, CSI, T_RED, CSI, T_PURPLE);
		printf("\t\t\t\t\t*\t%s%s ***********%s%s\t | \t%s%s ***********%s%s\t*\n", CSI, T_YELLOW, CSI, T_PURPLE, CSI, T_RED, CSI, T_PURPLE);
	}
	else if(inimigo->atordoado == 'S')
	{
		printf("\t\t\t\t\t*\t%s%s ***********%s%s\t | \t%s%s ***********%s%s\t*\n", CSI, T_BLUE, CSI, T_PURPLE, CSI, T_YELLOW, CSI, T_PURPLE);
		printf("\t\t\t\t\t*\t%s%s ***********%s%s\t | \t%s%s *ATORDOADO*%s%s\t*\n", CSI, T_BLUE, CSI, T_PURPLE, CSI, T_YELLOW, CSI, T_PURPLE);
		printf("\t\t\t\t\t*\t%s%s ***********%s%s\t | \t%s%s ***********%s%s\t*\n", CSI, T_BLUE, CSI, T_PURPLE, CSI, T_YELLOW, CSI, T_PURPLE);
	}
	else
	{
		printf("\t\t\t\t\t*\t%s%s ***********%s%s\t | \t%s%s ***********%s%s\t*\n", CSI, T_BLUE, CSI, T_PURPLE, CSI, T_RED, CSI, T_PURPLE);
		printf("\t\t\t\t\t*\t%s%s ***********%s%s\t | \t%s%s ***********%s%s\t*\n", CSI, T_BLUE, CSI, T_PURPLE, CSI, T_RED, CSI, T_PURPLE);
		printf("\t\t\t\t\t*\t%s%s ***********%s%s\t | \t%s%s ***********%s%s\t*\n", CSI, T_BLUE, CSI, T_PURPLE, CSI, T_RED, CSI, T_PURPLE);
	}
	printf("\n");
	barraDeVida(player, 0);
	barraDeVida(inimigo, 1);
}

void imprimeInterrogacao()
{
	printf("\n\n\n%s%s", CSI, T_PURPLE);
	printf("\t\t\t\t\t		      ,wggggMMMM0MM@@@@@@@MMMMMM0Mgggyy,____\n");
	printf("\t\t\t\t\t	    wmM#$$g#@MM@\"\"`                    `\"\"MMMMMMMMMMgy\n");
	printf("\t\t\t\t\t	  __wmM#$$g#@MM@\"\"`                    `\"\"MMMMMMMMMMgy__\n");
	printf("\t\t\t\t\t	y0@OwDMMMMMMM                               ^QMMMMMMMMMM0g\n");
	printf("\t\t\t\t\t	#@g2$0MMMMMf                                 jMNEMMMMMMMM0\n");
	printf("\t\t\t\t\t	 \"90#MMMMMMMg                             _jMM#0MMMMMMMM'\n");
	printf("\t\t\t\t\t	    #MMMMMMMg                             _jMM#0MMMMMM\n");
	printf("\t\t\t\t\t	      `\"\"9MMMMMm,__                 __,yM$ZW0MM@M\"\"`\n");
	printf("\t\t\t\t\t	                 ```^~       __ygMMMM\"^^`\n");
	printf("\t\t\t\t\t	                        _wmM$MME\n");
	printf("\t\t\t\t\t	                     jgQ#j&MMMMMM0Am,\n");
	printf("\t\t\t\t\t	                     9MM#0MMMMMMMMM0M\n");
	printf("\t\t\t\t\t	                          ``````\n");
	printf("\n");
	printf("\t\t\t\t\t	                        _,wawyywy_\n");
	printf("\t\t\t\t\t	                      MZ04WMMMNMMMM0\n");
	printf("\t\t\t\t\t	                       \"9NMMMMMM@M\"`\n");

}

/*Você deseja continuar jogando?*/
void continuarJogando(char *sn)
{
	do
	{
		system("clear");
		if(*sn != 's' && *sn != 'S' && *sn != 'n' && *sn != 'N')
			printf("\t\t\t\t\t%s%sENTRADA INVALIDA!!!%s%s\n", CSI, T_RED, CSI, T_PURPLE);
		imprimeInterrogacao();
		printf("\t\t\t\t\tDeseja continuar Jogando?\n\t\t\t\t\tS = Sim\n\t\t\t\t\tN = Nao\n\t\t\t\t\t");
		scanf(" %c", sn);
		limpaBuffer();
	}while(*sn != 's' && *sn != 'S' && *sn != 'n' && *sn != 'N');
	printf("%s%s", CSI, T_WHITE);
}

/*entrada invalida retorna 1*/
int escolhaAtack(int *atk)
{
	printf("%s%s", CSI, T_PURPLE);
	printf("\n\t\t\t\t\tEscolha a sua opcao\n");
	printf("\t\t\t\t\t0 - Fugir\n");
	printf("\t\t\t\t\t1 - Atack Rapido\n");
	printf("\t\t\t\t\t2 - Atack Forte\n");
	printf("\t\t\t\t\t3 - Defesa\n");
	printf("\t\t\t\t\t4 - Usar Porcao\n%s%s", CSI, T_WHITE);
	printf("\n\t\t\t\t\tOBS: Se voce nao tiver porcao e tentar usar, sera uma rodada em vão\n\t\t\t\t\t");
	if(!scanf("%d", atk) || *atk > 4 || *atk < 0)
	{
		limpaBuffer();
		system("clear");
		printf("\t\t\t\t\t%s%sENTRADA INVALIDA !!!!%s%s\n", CSI, T_RED, CSI, T_WHITE);
		return 1;
	}
	return 0;
}

void inimigoAtack(vampiro *inimigo, int *atkInimigo)
{
	if(inimigo->hpMax <= 100)
	{
		if(inimigo->porcoes_usadas < inimigo->num_porcoes && inimigo->hp < inimigo->hpMax/2)
			*atkInimigo = 1+rand()%4;
		else
			*atkInimigo = 1+rand()%3;
		return;
	}
	else
	{
		int hp = inimigo->hp;
		int hpm = inimigo->hpMax;
		int p; /*p de probabilidade*/
		if(hp < hpm/4)
		{
			p = rand()%8;
			if(p == 0)
				*atkInimigo = 1;
			else if(p == 1)
				*atkInimigo = 2;
			else if(p%2 == 0)
				*atkInimigo = 3;
			else
			{
				if(inimigo->porcoes_usadas < inimigo->num_porcoes)
					*atkInimigo = 4;
				else
					*atkInimigo = 1+rand()%3;
			}
		}
		else
		{
			p = rand()%8;
			if(p == 0)
			{
				if(inimigo->porcoes_usadas < inimigo->num_porcoes)
					*atkInimigo = 4;
				else
					*atkInimigo = 1+rand()%3;
			}
			else if(p == 1)
				*atkInimigo = 3;
			else if(p%2 == 0)
				*atkInimigo = 2;
			else
				*atkInimigo = 1;
		}
	}
}

void usarPorcao(vampiro *vamp)
{
	if(vamp->porcoes_usadas < vamp->num_porcoes)
	{
		vamp->hp = vamp->hp + 30;
		if(vamp->hp > vamp->hpMax)
			vamp->hp = vamp->hpMax;
		vamp->porcoes_usadas = vamp->porcoes_usadas+1;
		printf("\t\t\t\t\t%s usou porcao\n", vamp->nome);
	}
	else
	{
		printf("\t\t\t\t\t%s excedeu o numero de porcoes usadas\n", vamp->nome);
	}
}

/*Vai atacar? se sim retorna 1, senão 0*/
int vaiAtarcar(vampiro *vamp)
{
	int p = rand()%100;
	if(p < vamp->precisao)
		return 1;
	return 0;
}

/*v1 ataca rapido v2, se v2 morrer retorna 1*/
int atackRapido(vampiro *v1, vampiro *v2)
{
	v2->hp = v2->hp - v1->atack;
	v1->hp = v1->hp + v1->life_steal;
	if(v1->hp > v1->hpMax)
		v1->hp = v1->hpMax;
	printf("\t\t\t\t\t%s usou atack rapido em %s\n", v1->nome, v2->nome);
	if(v2->hp < 0)
		return 1;
	return 0;
}

/*Ficará atordoado?*/
void atordoado(vampiro *vamp, int probabil)
{
	int p;
	p = rand()%100;
	if(p < (100-probabil))
		vamp->atordoado = 'N';
	else
		vamp->atordoado = 'S';
}

/*v1 ataca Forte v2, se v2 morrer retorna 1*/
int atackForte(vampiro *v1, vampiro *v2)
{
	v2->hp = v2->hp - 2*(v1->atack);
	atordoado(v1, v1->precisao);
	printf("\t\t\t\t\t%s usou atack Forte em %s\n", v1->nome, v2->nome);
	if(v2->hp < 0)
		return 1;
	return 0;
}

/*retorna 1 se alguem morreu*/
int somente1Batendo(vampiro *vamp1, int atk, vampiro *vamp2)
{
	if(atk == 1)
	{
		if(atackRapido(vamp1, vamp2))
			return 1;
		return 0;
	}
	if(atk == 2)
	{
		if(atackForte(vamp1, vamp2))
			return 1;
		return 0;
	}
	if(atk == 3)
	{
		vamp1->hp = vamp1->hp+(vamp1->hpMax)/10;
		if(vamp1->hp > vamp1->hpMax)
			vamp1->hp = vamp1->hpMax;
		printf("\t\t\t\t\t%s ganhou HP\n", vamp1->nome);
		return 0;
	}
	if(atk == 4)
		usarPorcao(vamp1);
	return 0;
}

/*AR vs AR, se player morreu retorna 1, se inimigo morreu retorna 2*/
int aRxaR(vampiro *player, vampiro *inimigo)
{
	if(player->precisao >= inimigo->precisao)
	{
		printf("%s%s", CSI, T_BLUE);
		if(atackRapido(player, inimigo))
			return 2;
		printf("%s%s", CSI, T_RED);
		if(atackRapido(inimigo, player))
			return 1;
	}
	else
	{
		printf("%s%s", CSI, T_RED);
		if(atackRapido(inimigo, player))
			return 1;
		printf("%s%s",CSI, T_BLUE );
		if(atackRapido(player, inimigo))
			return 2;
	}
	return 0;
}

/*AF vs AF, player morreu? retorna 1, se inimigo morreu retorna 2*/
int aFxaF(vampiro *player, vampiro *inimigo)
{
	if(player->precisao >= inimigo->precisao)
	{
		printf("%s%s", CSI, T_BLUE);
		if(atackForte(player, inimigo))
			return 2;
		printf("%s%s", CSI, T_RED);
		if(atackForte(inimigo, player))
			return 1;
	}
	else
	{
		printf("%s%s", CSI, T_RED);
		if(atackForte(inimigo, player))
			return 1;
		printf("%s%s", CSI, T_BLUE);
		if(atackForte(player, inimigo))
			return 2;
	}
	return 0;
}

/*Defendendo vs Qualquer Outra escolha
 *vamp1 defendendo, vamp2 atacando
 */
int defend(vampiro *vamp1, vampiro *vamp2, int atk, const char *COR1, const char *COR2)
{
	int precisao = vamp2->precisao;
	int atack = vamp2->atack;
	if(atk == 1)
		vamp2->precisao = 2*(100-precisao);
	if(atk == 2)
		vamp2->precisao = 100;
	vamp2->atack = atack/2;
	printf("%s%s", CSI, COR1);
	printf("\t\t\t\t\t%s esta se defendendo\n", vamp1->nome);
	printf("%s%s", CSI, COR2);
	if(somente1Batendo(vamp2, atk, vamp1))
	{
		vamp2->atack = atack;
		vamp2->precisao = precisao;
		return 1;
	}
	vamp2->atack = atack;
	vamp2->precisao = precisao;
	if(atk == 3 || atk == 4) /*DxD ou DxUsarPorcao*/
	{
		vamp1->hp = vamp1->hp+((vamp1->hpMax)/10);
		if(vamp1->hp > vamp1->hpMax)
			vamp1->hp = vamp1->hpMax;
		printf("%s%s", CSI, COR1);
		printf("\t\t\t\t\t%s ganhou HP\n", vamp1->nome);
	}
	printf("%s%s", CSI, T_WHITE);
	return 0;
}

/*retorna 1 se player morreu, e retorna 2 se vampiro morreu.
 *Só um re-salve que se um dos personagem não for atacar a or-
 *dem de precedência de atack não importa.
 */
int resultado(vampiro *player, int atk, vampiro *inimigo, int atkInimigo)
{
	if(player->atordoado == 'N' && inimigo->atordoado == 'N')
	{
		int a, b;
		a = vaiAtarcar(player);
		b = vaiAtarcar(inimigo);
		if(a == 0 && b == 0)
		{
			printf("%s%s", CSI, T_BLUE);
			printf("\t\t\t\t\t%s nao conseguiu atacar\n", player->nome);
			printf("%s%s", CSI, T_RED);
			printf("\t\t\t\t\t%s nao conseguiu atacar\n", inimigo->nome);
			printf("%s%s", CSI, T_WHITE);
			return 0;
		}
		else if(a == 1 && b == 0)
		{
			printf("%s%s", CSI, T_RED);
			printf("\t\t\t\t\t%s nao conseguiu atacar\n", inimigo->nome);
			printf("%s%s", CSI, T_BLUE);
			if(somente1Batendo(player, atk, inimigo) && printf("%s%s", CSI, T_WHITE))
				return 2;
			return 0;
		}
		else if(a == 0 && b == 1)
		{
			printf("%s%s", CSI, T_BLUE);
			printf("\t\t\t\t\t%s nao conseguiu atacar\n", player->nome);
			printf("%s%s", CSI, T_RED);
			if(somente1Batendo(inimigo, atkInimigo, player) && printf("%s%s", CSI, T_WHITE))
				return 1;
			return 0;
		}
		else
		{
			/*Estou supondo que usar porção é
			 *sempre mais rapido que atacar ou defender
			 *pois isso é de se esperar.
			 *Além disso quando um usa porção e
			 *o outro se defende a ordem também
			 *não importa.
			 */
			if(atk == 4)
			{
				printf("%s%s",CSI, T_BLUE );
				usarPorcao(player);
				printf("%s%s", CSI, T_RED);
				if(somente1Batendo(inimigo, atkInimigo, player) && printf("%s%s", CSI, T_WHITE))
					return 1;
				return 0;
			}
			if(atkInimigo == 4)
			{
				printf("%s%s",CSI, T_RED );
				usarPorcao(inimigo);
				printf("%s%s", CSI, T_BLUE);
				if(somente1Batendo(player, atk, inimigo) && printf("%s%s", CSI, T_WHITE))
					return 2;
				return 0;
			}
			if(atk == 3)
			{
				if(defend(player, inimigo, atkInimigo, T_BLUE, T_RED))
					return 1;
				return 0;
			}
			if(atkInimigo == 3)
			{
				if(defend(inimigo, player, atk, T_RED, T_BLUE))
					return 2;
				return 0;
			}
			if(atk == 2)
			{
				if(atkInimigo == 1)
				{
					printf("%s%s", CSI, T_RED);
					if(somente1Batendo(inimigo, atkInimigo, player))
						return 1;
					printf("%s%s", CSI, T_BLUE);
					if(somente1Batendo(player, atk, inimigo))
						return 2;
					return 0;
				}
				return aFxaF(player, inimigo);
			}
			if(atk == 1)
			{
				if(atkInimigo == 2)
				{
					printf("%s%s", CSI, T_BLUE);
					if(somente1Batendo(player, atk, inimigo))
						return 2;
					printf("%s%s", CSI, T_RED);
					if(somente1Batendo(inimigo, atkInimigo, player))
						return 1;
					return 0;
				}
				return aRxaR(player, inimigo);
			}
		}
	}
	else if(player->atordoado == 'N' && inimigo->atordoado == 'S')
	{
		printf("%s%s",CSI, T_RED );
		printf("\t\t\t\t\t%s estar atordoado%s%s\n", inimigo->nome, CSI, T_BLUE);
		inimigo->atordoado = 'N';
		if(somente1Batendo(player, atk, inimigo) && printf("%s%s", CSI, T_WHITE))
			return 2;
		return 0;
	}
	else if(player->atordoado == 'S' && inimigo->atordoado == 'N')
	{
		printf("%s%s", CSI, T_BLUE);
		printf("\t\t\t\t\t%s estar atordoado%s%s\n", player->nome, CSI, T_RED);
		player->atordoado = 'N';
		if(somente1Batendo(inimigo, atkInimigo, player) && printf("%s%s", CSI, T_WHITE))
			return 1;
		return 0;
	}
	else
	{
		printf("\t\t\t\t\t%s%s%s esta atordoado\n%s%s", CSI, T_BLUE, player->nome, CSI, T_RED);
		printf("\t\t\t\t\t%s esta atordoado%s%s\n", inimigo->nome, CSI, T_WHITE);
		player->atordoado = 'N';
		inimigo->atordoado = 'N';
	}
	return 0;
}


void imprimeFrango()
{
	printf("\n\n\n");
	printf("\t\t\t\t\t\t\t             %s%sxx%s%s\n", CSI, T_RED, CSI, T_WHITE);
	printf("\t\t\t\t\t\t\t            / %s%s0%s%s|_\n", CSI, T_BLUE, CSI, T_WHITE);
	printf("\t\t\t\t\t\t\t           /(_)_%s%s<%s%s\n", CSI, T_YELLOW, CSI, T_WHITE);
	printf("\t\t\t\t\t\t\t          /  (\n");
	printf("\t\t\t\t\t\t\t ((____.-'    )\n");
	printf("\t\t\t\t\t\t\t  \\\\         /\n");
	printf("\t\t\t\t\t\t\t   \\'-.-.-'`/\n");
	printf("\t\t\t\t\t\t\t %s%s_%s%s  \\______/\n", CSI, T_YELLOW, CSI, T_WHITE);
	printf("\t\t\t\t\t\t\t%s%s(_)   _|_\\_%s%s\n", CSI, T_YELLOW, CSI, T_WHITE);
	printf("\t\t\t\t\t''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
}

void aperteEnter(char *sn)
{
	system("clear");
	imprimeFrango();
	printf("\t\t\t\t\tVoce nao eh um vampiro, eh apenas um HOMEM MOSQUITO!!!!\n");
	limpaBuffer();
	printf("\t\t\t\t\tAperte enter\n\t\t\t\t\t");
	limpaBuffer();
	continuarJogando(sn);
}

/*Se voce perder essa imagem ira aparecer*/
void imprimeCaveira()
{
	system("clear");
	char a = '%';
	printf("%s%s\n\n\t\t\t\t	                     .ed\"\"\"\" \"\"\"$$$$be.\n", CSI, T_RED);
	printf("\t\t\t\t	                   -\"           ^\"\"**$$$e.\n");
	printf("\t\t\t\t	                 .\"                   '$$$c\n");
	printf("\t\t\t\t	                /                      \"4$$b\n");
	printf("\t\t\t\t	               d  3                      $$$$\n");
	printf("\t\t\t\t	               $  *                   .$$$$$$\n");
	printf("\t\t\t\t	              .$  ^c           $$$$$e$$$$$$$$.\n");
	printf("\t\t\t\t	              d$L  4.         4$$$$$$$$$$$$$$b\n");
	printf("\t\t\t\t	              $$$$b ^ceeeee.  4$$ECL.F*$$$$$$$\n");
	printf("\t\t\t\t	  e$\"\"=.      $$$$P d$$$$F $ $$$$$$$$$- $$$$$$\n");
	printf("\t\t\t\t	 z$$b. ^c     3$$$F \"$$$$b   $\"$$$$$$$  $$$$*\"      .=\"\"$c\n");
	printf("\t\t\t\t	4$$$$L        $$P\"  \"$$b   .$ $$$$$...e$$        .=  e$$$.\n");
	printf("\t\t\t\t	^*$$$$$c  %c..   *c    ..    $$ 3$$$$$$$$$$eF     zP  d$$$$$\n", a);
	printf("\t\t\t\t	  \"**$$$ec   \"   %cce\"\"    $$$  $$$$$$$$$$*    .r\" =$$$$P\"\"\n", a);
	printf("\t\t\t\t	        \"*$b.  \"c  *$e.    *** d$$$$$\"L$$    .d\"  e$$***\"\n");
	printf("\t\t\t\t	          ^*$$c ^$c $$$      4J$$$$$%c $$$ .e*\".eeP\"\n", a);
	printf("\t\t\t\t	             \"$$$$$$\"'$=e....$*$$**$cz$$\" \"..d$*\"\n");
	printf("\t\t\t\t	               \"*$$$  *=%c4.$ L L$ P3$$$F $$$P\"\n", a);
	printf("\t\t\t\t	                  \"$   \"%c*ebJLzb$e$$$$$b $P\"\n", a);
	printf("\t\t\t\t	                    %c..      4$$$$$$$$$$ \"\n", a);
	printf("\t\t\t\t	                     $$$e   z$$$$$$$$$$%c\n", a);
	printf("\t\t\t\t	                      \"*$c  \"$$$$$$$P\"\n");
	printf("\t\t\t\t	                       .\"\"\"*$$$$$$$$bc\n");
	printf("\t\t\t\t	                    .-\"    .$***$$$\"\"\"*e.\n");
	printf("\t\t\t\t	                 .-\"    .e$\"     \"*$c  ^*b.\n");
	printf("\t\t\t\t	          .=*\"\"\"\"    .e$*\"          \"*bc  \"*$e..\n");
	printf("\t\t\t\t	        .$\"        .z*\"               ^*$e.   \"*****e.\n");
	printf("\t\t\t\t	        $$ee$c   .d\"                     \"*$.        3.\n");
	printf("\t\t\t\t	        ^*$E\")$..$\"                         *   .ee==d%c\n", a);
	printf("\t\t\t\t	           $.d$$$*                           *  J$$$e*\n");
	printf("\t\t\t\t	            \"\"\"\"\"                              \"$$$\"\n");

}

void imprimeGoodLuck()
{
	system("clear");
	printf("%s%s", CSI, T_PURPLE);
	printf("\n\n\n\n\n\n");
	printf("\t\t\t\t\t ___  ___  ___  ___              ___\n");
	printf("\t\t\t\t\t|    |   ||   ||   \\   |   |   ||    | / \n");
	printf("\t\t\t\t\t| --;|   ||   ||   |   |   |   ||    |< \n");
	printf("\t\t\t\t\t|___||___||___||___/   |__ |___||___ | \\ \n");
	printf("\n\n");
	printf("\t\t\t\t\tAperte Enter\n");
	limpaBuffer();
}

/*Se enfrentar o Dracula ou o Alucard irá aparecer essa imagem*/
void imprimeDracula(vampiro *player, vampiro *inimigo)
{
	char a = '%';
	system("clear");
	printf("\t\t		              ...;;;;;;;;;;;;;;;;;;;;;;;;;;;...\n");
	printf("\t\t	                 ,;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;.\n");
	printf("\t\t	               .;;;;;;;|;;;|;;|;;;;;;|;;|;;;|;;;|;;;;;:;;;\n");
	printf("\t\t	             .;;:::::::::|:::|::||::::::::::::::::::; ;;;;`;\n");
	printf("\t\t	           ;;;:::::::|:|:::|::|:||::|::|::||::|::::;   ;::::`;\n");
	printf("\t\t	          ;::::::::::::::|:::|::||::::|:|::::|::::,' .;;;;;;;;;\n");
	printf("\t\t	         ;;:::::::::`:|:::::::::'`;;;;;;;;;;;;;'     :;;;);;;;;;\n");
	printf("\t\t	        ;;;::::(:::;  ``````````  ''''''''''''        :;;;(;;;;;\n");
	printf("\t\t	       ;;;::::):;;'                                   ``.;;);;;;;\n");
	printf("\t\t	      ;;;:::(::;                                        `;;;(;;;;;\n");
	printf("\t\t	     ;;;::::::; %c          .             .               :;;;;;;;;\n", a);
	printf("\t\t	    _;;;;;;);;  %c%c,          .    .   .                  :;;;;;;;;\n", a, a);
	printf("\t\t	    \\;;;;;;;;' %c%c%c%c   :::                                 :;);;;;\n", a, a, a, a);
	printf("\t\t	     \\;;;;(;: %c%c%c  '   :::   ,         \"                  :(;;;;;\n", a, a, a);
	printf("\t\t	    _  \\;;;|             ::  x. |  |,'                    :;);;;  _\n");
	printf("\t\t	    )\\  \\;;:    `%c##%c#%c       Xx :  #%c        %c####%c.,,    :;;;  /(\n", a, a, a, a, a, a);
	printf("\t\t	    \\ (_ \\;|        ;###%c.   XX    :##%c.     ,##.   \"      |;; _) /\n", a, a);
	printf("\t\t	     \\  \\_::`  _   .%c########:;  ;  `###########h.,- _   ,  :_/  /\n", a);
	printf("\t\t	      \\  ]|:: = XX%cx < (_)  )``""   \\`%c( (_)  >      _ =    |[  /\n", a, a);
	printf("\t\t	       :  |::. ~  %c   `----'x#|      ; %c`----'        ~     |  :\n", a, a);
	printf("\t\t	       :  |:::     %c        X#:      `  xXx                 |  :\n", a);
	printf("\t\t	      |   |:::      `xxxxd'  #|         ` `dxxxxx\"          |  |\n");
	printf("\t\t	      |   |::'              x#|                             |  |\n");
	printf("\t\t	      |   |::.           __ X#:      ;::::;;;;              |` |\n");
	printf("\t\t	       \\_ |::::.       ,;;;;x#|       \"\"\"\\ ;;;              |_/\n");
	printf("\t\t	         \\_:::::      .;;(CCc%c:           |;;;::::::::;\"\"  |/\n", a);
	printf("\t\t	           :%c:::......;' `CCc`-.        ,-'  `:::::::'     :\n", a);
	printf("\t\t	           `%c%c%c%c::~~~~         `.    _,'       ~~~~~ ;;    ;\n", a, a, a, a);
	printf("\t\t	            `;%c;:'               `--'            .   ))   ,'\n", a);
	printf("\t\t	             `;;' ::::'_    ______\"\"______    _,%c;  ;:'  ,'\n", a);
	printf("\t\t	         _____`,  :::  )`--'\\    /`' \\    `--'( `;  '   ,____\n");
	printf("\t\t	      __/######`,  `:   \\----\\  /-----\\  /---/   `     ,'####\\\n");
	printf("\t\t	     /##########`,   `   `--._\\/_______\\/,--'        ,'#######\\\n");
	printf("\t\t	   _/############`-.__        , ~~~~~~`         __,-'#####x####\\\n");
	printf("\t\t	  /#########x#########`-._             `    _,-'|##########x####\\\n");
	printf("\t\t	 /#########x#########/|@@@`-._     ^     _,'@@|n|###########x#####\\\n");
	printf("\t\t	/#########x#########/ |@@@@@@@`----'`---'@@@@@@|n|###########x####/\n");
	printf("\n\n\t\t\t\t\t%s ira enfrentar %s\n", player->nome, inimigo->nome);
	printf("\t\t\t\t\tAperte enter\n");
	limpaBuffer();
	imprimeGoodLuck();
}

void imprimeMorcego()
{
	system("clear");
	printf("%s%s\n",CSI, T_PURPLE );
	printf("\t\t\t\t\t	    ####### \n");
	printf("\t\t\t\t\t	    ######## \n");
	printf("\t\t\t\t\t	    ######## \n");
	printf("\t\t\t\t\t	    ######### \n");
	printf("\t\t\t\t\t	    ########## \n");
	printf("\t\t\t\t\t	   ############ \n");
	printf("\t\t\t\t\t	 ############## \n");
	printf("\t\t\t\t\t	################ \n");
	printf("\t\t\t\t\t	 ################ \n");
	printf("\t\t\t\t\t	   ############## \n");
	printf("\t\t\t\t\t	    ##############                                              #### \n");
	printf("\t\t\t\t\t	    ##############                                           ##### \n");
	printf("\t\t\t\t\t	     ##############                                      ####### \n");
	printf("\t\t\t\t\t	     ##############                                 ########### \n");
	printf("\t\t\t\t\t	     ###############                              ############# \n");
	printf("\t\t\t\t\t	     ################                           ############## \n");
	printf("\t\t\t\t\t	    #################      #                  ################ \n");
	printf("\t\t\t\t\t	    ##################     ##    #           ################# \n");
	printf("\t\t\t\t\t	   ####################   ###   ##          ################# \n");
	printf("\t\t\t\t\t	        ################  ########          ################# \n");
	printf("\t\t\t\t\t	         ################  #######         ################### \n");
	printf("\t\t\t\t\t	           #######################       ##################### \n");
	printf("\t\t\t\t\t	            #####################       ################### \n");
	printf("\t\t\t\t\t	              ############################################ \n");
	printf("\t\t\t\t\t	               ########################################### \n");
	printf("\t\t\t\t\t	               ########################################## \n");
	printf("\t\t\t\t\t	                ######################################## \n");
	printf("\t\t\t\t\t	                ######################################## \n");
	printf("\t\t\t\t\t	                 ###################################### \n");
	printf("\t\t\t\t\t	                 ###################################### \n");
	printf("\t\t\t\t\t	                  ##########################      ##### \n");
	printf("\t\t\t\t\t	                  ###  ###################           ## \n");
	printf("\t\t\t\t\t	                  ##    ############### \n");
	printf("\t\t\t\t\t	                  #     ##  ########## \n");
	printf("\t\t\t\t\t	                            ##    ### \n");
	printf("\t\t\t\t\t	                                  ### \n");
	printf("\t\t\t\t\t	                                  ## \n");
	printf("\t\t\t\t\t	                                  # \n");
}

void imprimeYouAreDead()
{
	printf("\t\t\t\t\t       ___                __   ___    ___  ___       ___\n");
	printf("\t\t\t\t\t \\   /|   ||   |    /\\   |  \\ |      |   \\|     /\\  |   \\\n");
	printf("\t\t\t\t\t  \\ / |   ||   |   /__\\  |__| |---   |   ||--- /__\\ |   |\n");
	printf("\t\t\t\t\t   |  |___||___|  /    \\ |  \\ |___   |___/|___/    \\|___/\n");
}

void imprimeYouWin()
{
	printf("\t\t\t\t\t\t          ___         \n");
	printf("\t\t\t\t\t\t    \\   /|   ||   |  |    |||\\  /|   __/__/__ \n");
	printf("\t\t\t\t\t\t     \\ / |   ||   |  | /\\ ||| \\/ |  __/__/__\n");
	printf("\t\t\t\t\t\t      |  |___||___|  |/  \\|||    |   /  /\n");
	printf("%s%s\n", CSI, T_WHITE);
}

int main()
{
	vampiro *inimigo, *player;
	inimigo = (vampiro *) malloc(sizeof(vampiro));
	player = (vampiro *) malloc(sizeof(vampiro));
	int atk = 5, atkInimigo = 0;
	char sn = 'S';/*Variavel 'sn' decide se jogador deseja ou nao continuar jogando*/
	int result;
	system("clear");
	iniciaPlayer(player);
	iniciaInimigo(inimigo);
	if(inimigo->hpMax > 100)
		imprimeDracula(player, inimigo);
	/*Laço principal do Jogo*/
	do
	{
		system("clear");
		imprVampiro(player, inimigo);
		while(escolhaAtack(&atk))
			imprVampiro(player, inimigo);
		if(atk == 0)
		{
			aperteEnter(&sn);
			if(sn == 'N' || sn == 'n')
				break;
			restartInimigo(inimigo);
			if(inimigo->hpMax > 100)
				imprimeDracula(player, inimigo);
			restartPlayer(player);
		}
		else if(atk > 0 && atk < 5)
		{
			inimigoAtack(inimigo, &atkInimigo);
			result = resultado(player, atk, inimigo, atkInimigo);
			limpaBuffer();
			printf("%s%s",CSI, T_YELLOW );
			printf("\t\t\t\t\tpress enter\n\t\t\t\t\t");
			printf("%s%s", CSI, T_WHITE);
			limpaBuffer();
			if(result == 1)
			{
				imprimeCaveira();
				imprimeYouAreDead();
				limpaBuffer();
				continuarJogando(&sn);
				if(sn == 'N' || sn == 'n')
					break;
				restartInimigo(inimigo);
				if(inimigo->hpMax > 100)
					imprimeDracula(player, inimigo);
				restartPlayer(player);
			}
			else if (result == 2)
			{
				imprimeMorcego();
				imprimeYouWin();
				limpaBuffer();
				continuarJogando(&sn);
				if(sn == 'N' || sn == 'n')
					break;
				restartInimigo(inimigo);
				if(inimigo->hpMax > 100)
					imprimeDracula(player, inimigo);
				restartPlayer(player);
			}
		}

	}while(atk >= 0 && atk < 5 && (sn != 'N' || sn != 'n'));
	free(player);
	free(inimigo);
	return 0;
}
