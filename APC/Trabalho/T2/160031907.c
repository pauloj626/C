/*		João Paulo Pinhiero Melo
 *			   16/0031907
 *Segundo trabalho de APC, prof: Guilherme N. Ramos
 *			RPG dos vampiros
 *Nesse jogo os vampiros inimigos NÃO pegam itens do jogo
 *pois em todos os jogos de RPG que eu já joguei os únicos
 *inimigos que a CPU controla que pega itens do player
 *são os Globins, dessa forma todos os vampiros inimigos
 *já vem com seu life_setal próprio e etc.
 *Caso você tente atravassar um parade não irá conseguir
 *atravessa-la dessa forma não é necessario imprimir messa-
 *gem indicando isso.
 *O número de poção no mapa é de apenas 5 no total, pois
 *se ficar aparecendo mais e mais porções no mapa, o jogo
 *ficará muito fácil. Dessa forma os únicos item que irão
 *re-aparecer são as armaduras e as armas, e somente irá
 *re-aparecer no mapa sem o Dracula.
 *Neste jogo quando o player for derrotado ele perde todo
 *o xp antes acumulado, porém não perde o seu nivel, man-
 *tendo suas abilidades (veja linha 1181).
 *Dica: Defender pode aumentar o HP, no inicio em que você
 *não tem poção.
 *Para um melhor aproveitamento do jogo, use o modo full
 *screen do terminal.
 *Caso você queira um puco mais de dificuldeda retire o
 *comentario da linha 1181.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __LINUX__
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    #define clrscrn() system("clear")
#else
    #include <conio.h>
    #include <windows.h>
    #define clrscrn() system("cls")
#endif

typedef struct vampiro {
    char nome[20];
    int nivel;
	int posX;
    int posY;
    int posZ;
    char forma;
    int hpMax;
	int hp;
	int atack;
	int life_steal;
	int precisao;
	int num_porcoes;
	int porcoes_usadas;
	char atordoado;
	int xp;
}vampiro;

/*Não há muitas modificaçõe nessa parte, onde as mais importantes se encontram na função
 *playGame(), que seria a main() do antigo trabalho 1*/
/************************************INICIO DA*******************************************/
/*****************************PARTE REFERENTE AO TRABALHO 1******************************/
/****************************************************************************************/

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

void limpaBuffer()
{
	while(getchar() != '\n');
}

void imprimeTitle()
{
	printf("%s%s  \t\t\t\t\t 	               __       __    ___   __%s%s\n", CSI, T_PURPLE, CSI, T_WHITE);
	printf("%s%s  \t\t\t\t\t   \\    /  /\\   |\\  /||  |  |  |  \\  |   | |%s%s\n", CSI, T_PURPLE, CSI, T_WHITE);
 	printf("%s%s  \t\t\t\t\t    \\  /  /__\\  | \\/ ||--'  |  |__|  |   | '--.%s%s\n", CSI, T_PURPLE, CSI, T_WHITE);
  	printf("%s%s  \t\t\t\t\t     \\/  /    \\ |    ||     |  |  \\  |___|  __|%s%s\n", CSI, T_PURPLE, CSI, T_WHITE);
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
		clrscrn();
		if(*sn != 's' && *sn != 'S' && *sn != 'n' && *sn != 'N')
			printf("\t\t\t\t\t%s%sENTRADA INVALIDA!!!%s%s\n", CSI, T_RED, CSI, T_PURPLE);
		imprimeInterrogacao();
		printf("\t\t\t\t\tDeseja continuar Jogando?\n\t\t\t\t\tS = Sim\n\t\t\t\t\tN = Nao\n\t\t\t\t\t");
		printf("OBS: Sera lido apenas o primeiro caracter\n\t\t\t\t\t");
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
		clrscrn();
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
	clrscrn();
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
	clrscrn();
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
	clrscrn();
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
	clrscrn();
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
	clrscrn();
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

void imprimeYouWin()
{
	printf("\t\t\t\t\t\t          ___               ___\n");
	printf("\t\t\t\t\t\t    \\   /|   ||   |  |    ||   ||\\  |   __/__/__ \n");
	printf("\t\t\t\t\t\t     \\ / |   ||   |  | /\\ ||   || \\ |  __/__/__\n");
	printf("\t\t\t\t\t\t      |  |___||___|  |/  \\||___||  \\|   /  /\n");
	printf("%s%s\n", CSI, T_WHITE);
}

/*Nesta funcão foi acrescentoda o ganho de xp, do player
 *Caso o player vença a batalha.
 */
int playGame(vampiro *player, vampiro *inimigo){
	int atk = 5, atkInimigo = 0;
	char sn = 'S';
	int result;
	clrscrn();
	if(inimigo->hpMax == 150)
		imprimeDracula(player, inimigo);
	do
	{
		clrscrn();
		imprVampiro(player, inimigo);
		while(escolhaAtack(&atk))
			imprVampiro(player, inimigo);
		if(atk == 0)
		{
			aperteEnter(&sn);
			if(sn == 'N' || sn == 'n')
				break;
			continue;
		}
		else
		{
			inimigoAtack(inimigo,&atkInimigo);
			result = resultado(player, atk, inimigo, atkInimigo);
			limpaBuffer();
			printf("%s%s",CSI, T_YELLOW );
			printf("\t\t\t\t\tpress enter\n\t\t\t\t\t");
			printf("%s%s", CSI, T_WHITE);
			limpaBuffer();
			if(result == 1)
			{
				imprimeCaveira();
				printf("\t\t\t\t\t\t\t\t\tVOCE PERDEU\n");
				printf("%s%s\n", CSI, T_WHITE);
				limpaBuffer();
				return -1;
			}
			else if (result == 2)
			{
				imprimeMorcego();
				imprimeYouWin();
				printf("\t\t\t\t\t\t\t\t%s ganhou %d de xp\n", player->nome, inimigo->nivel);
				printf("%s%s\n", CSI, T_WHITE);
				player->xp += inimigo->nivel;
				limpaBuffer();
				return 1;
			}
		}
	}while(sn != 'N' || sn != 'n');
	clrscrn();
	printf("%s%s\n", CSI, T_WHITE);
	return 0;
}

/*****************************************FIM DA*****************************************/
/*****************************PARTE REFERENTE AO TRABALHO 1******************************/
/****************************************************************************************/
#ifdef __LINUX__
/*As duas funções abaixo (getch() e kbhit()), são duas função
 *extremamente importantes para o jogo, sei o que elas fazem e
 *como usa-las porém não sei explicar o funcionamento interno de
 *cada uma delas, simplesmente peguei elas de um amigo o qual
 *é monitor da disciplina.*/
char getch()/*<<-- le um caracter da entrada padrão sem o bloqueio de entrada(nao necessita apertar enter) */
{
    int ch;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO,&oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int kbhit(void) /*<<-- Checa se o Buffer estar vazio ou não*/
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
      ungetc(ch, stdin);
      return 1;
    }

    return 0;
}
#endif
int existVampNessaPosicao(int x, int y, vampiro *inimigos){
	int i = 0;
	while(i < 12 && (inimigos[i].posY != x || inimigos[i].posX != y))
		i++;
	return (i == 12)?-1:i;
}

void imprimiMap(char mapa1[3][130][130], vampiro *player, vampiro *inimigos, vampiro *dracula){
	int i, j, k;
	if(!player->posZ){
		for(i = 0; i < 28; i++){
			for(j = 0; j < 85; j++){
				k = existVampNessaPosicao(i, j, inimigos);
				if(player->posX == j && player->posY == i)
					putchar(player->forma);
				else if(k > -1)
					putchar(inimigos[k].forma);
				else
					putchar(mapa1[player->posZ][i][j]);
			}
			putchar('\n');
		}
	}
	else{
		for(i = 0; i < 28; i++){
			for(j = 0; j < 85; j++){
				if(player->posX == j && player->posY == i)
					putchar(player->forma );
				else if(dracula->posX == j && dracula->posY == i)
					putchar('D');
				else
					putchar(mapa1[player->posZ][i][j]);
			}
			putchar('\n');
		}
	}
}

void limpaBufferComKbhit(){
    while(kbhit()) getch();
}

void iniciaPosPlayer(vampiro *player){
	player->posX = 2;
	player->posY = 25;
	player->posZ = 0;
}

void completaNome(char *nome){
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

void iniciaPlayer(vampiro *player){
	char nome[20];
	printf("Digite seu nome(apenas 7 caracteres):\n");
	scanf("%7[^\n]", nome); /* <<-- O nome estar limitado a 7 caracteres é proposital*/
	completaNome(nome);
	while(getchar() != '\n');
	strcpy(player->nome, nome);
	player->hpMax = 50;
	player->hp = player->hpMax;
	player->atack = 6;
	player->life_steal = 0;
	player->precisao = 55;
	player->num_porcoes = 1;
	player->porcoes_usadas = 0;
	player->atordoado = 'N';
	player->forma = '@';
	player->xp = 0;
	player->nivel = 1;
	iniciaPosPlayer(player);
}


void iniciaPosInimigos(vampiro *inimigos, vampiro *dracula){
	int i;
	for(i = 0; i < 4; i++){
		inimigos[i].posZ = 0;
		inimigos[i].posX = 19*(1+(i%4));
		inimigos[i].posY = 25 - 10*(i/4);
	}
	for(; i < 8; i++){
		inimigos[i].posZ = 0;
		inimigos[i].posX = 19*(4-(i%4));
		inimigos[i].posY = 25 - 10*(i/4);
	}
	for(; i < 12; i++){
		inimigos[i].posZ = 0;
		inimigos[i].posX = 14*(1+i%4);
		inimigos[i].posY = 5;
	}
	dracula->posZ = 1;
	dracula->posX = 43;
	dracula->posY = 12;
}

/*Os atributos que usei para iniciar o inimigo são diferentes
 *do especificado pois acredito que estes estejam mais "equilibrados"
 */
void iniciaInimigo(vampiro *inimigos, vampiro *dracula){
	int i;
	for(i = 0; i < 12; i++){
		strcpy(inimigos[i].nome, "Inimigo");
		inimigos[i].hpMax = 20*(2+i/3);
		inimigos[i].hp = inimigos[i].hpMax;
		inimigos[i].atack = 2+i;
		inimigos[i].life_steal = i+2;
		inimigos[i].precisao = 30+(10*i)/3;
		inimigos[i].num_porcoes = (5*i)/12;
		inimigos[i].porcoes_usadas = 0;
		inimigos[i].atordoado = 'N';
		inimigos[i].forma = 'V';
		inimigos[i].nivel = i+1;
	}
	strcpy(dracula->nome, "DRACULA");
	dracula->hpMax = 150;
	dracula->hp = dracula->hpMax;
	dracula->atack = 20;
	dracula->life_steal = 10;
	dracula->precisao = 30;
	dracula->num_porcoes = 2;
	dracula->porcoes_usadas = 0;
	dracula->atordoado = 'N';
	dracula->forma = 'D';
	dracula->nivel = 12;
	iniciaPosInimigos(inimigos, dracula);
}

void escolherCoordenadaValidaParaItem(char mapa[3][130][130]){
	int x, y, qualItem;
	do{
		x = rand()%27;
		y = rand()%85;
	}while(mapa[0][x][y] != ' ');
	qualItem = rand()%2;
	if(!qualItem)
		mapa[0][x][y] = 'W';
	else
		mapa[0][x][y] = 'A';
}

void setItemNoMapa(char mapa[3][130][130], int *numero_de_itens_no_mapa){
	/*Se o numero de item no mapa é maior ou igual
	 *a três, não há necessidade de mais item no jogo*/
	if((*numero_de_itens_no_mapa) < 3){
		/*Coloca item na coordenada valida*/
		escolherCoordenadaValidaParaItem(mapa);
		(*numero_de_itens_no_mapa) = 3;
	}
}

void setItemPlayer(vampiro *player, char mapa[3][130][130], int *numero_de_itens_no_mapa){
	char icon = mapa[player->posZ][player->posY][player->posX];
	if(icon == 'P' || icon == 'A' || icon == 'W'){
		if(!(player->posZ))   /* <<-- Somente itens no primeiro mapa*/
			(*numero_de_itens_no_mapa) -= 1; /*um item a menos no mapa*/
		if(icon == 'P'){
			player->num_porcoes = 5;
			player->porcoes_usadas = 0;
		}
		else if(icon == 'A'){                                    /*Armadura*/
			player->atack = (6 + ((player->nivel)/2)) - 2;       /*diminui o atack em 2*/
			player->life_steal = ((player->nivel)/3) + 10;       /*aumenta o life_steal em 10*/
			player->precisao = (55 + 2*(player->nivel)) + 15;    /*aumenta a precisão em 15*/
		}
		else{                                                    /*Arma*/
			player->atack = (6 + ((player->nivel)/2)) + 6;       /*aumenta o atack do player em 6*/
		}
		mapa[player->posZ][player->posY][player->posX] = ' ';
	}
	/*Essa função pode dar uma pequena pausa no jogo*/
	setItemNoMapa(mapa, numero_de_itens_no_mapa);
}

void movePlayer(vampiro *player, char dir, char mapa[3][130][130]){
	if(dir == 'd'){
			player->posX++;
			if(mapa[player->posZ][player->posY][player->posX] == '#' || mapa[player->posZ][player->posY][player->posX] == '+')
				player->posX--;
	}
	else if(dir == 'a'){
		player->posX--;
		if(mapa[player->posZ][player->posY][player->posX] == '#' || mapa[player->posZ][player->posY][player->posX] == '+')
			player->posX++;

	}
	else if(dir == 'w'){
		player->posY--;
		if(mapa[player->posZ][player->posY][player->posX] == '#' || mapa[player->posZ][player->posY][player->posX] == '+')
			player->posY++;
	}
	else if(dir == 's'){
		player->posY++;
		if(mapa[player->posZ][player->posY][player->posX] == '#' || mapa[player->posZ][player->posY][player->posX] == '+')
			player->posY--;
	}
	if(mapa[player->posZ][player->posY][player->posX] == 'T'){
		player->posX = 2;
		player->posY = 2+(23*player->posZ);
		player->posZ = !(player->posZ);
	}
}

void moveInimigos(vampiro *inimigos, vampiro *dracula, char mapa[3][130][130]){
	int i, x, y;
	for(i = 0; i < 12; i++){
		x = inimigos[i].posX + (rand()-rand())%2;
		y = inimigos[i].posY + (rand()-rand())%2;
		if(mapa[0][y][x] == ' '){ /*Só moverá se estiver espaço vazio*/
			inimigos[i].posX = x;
		    inimigos[i].posY = y;
		}
		/*Quando o inimigo se move ele ganha HP
		 *Se ele não foi derrotado (forma == 'V') ganha 1 de HP
		 *Caso contrario se ele foi derrotado (forma == 'M') ganha 2 de HP
		 *Se um vampiro derrotado recupera 100% de seu HP, ele volta
		 *à batalhar (forma == 'M' passa a ser forma == 'V')*/
		if(inimigos[i].forma == 'V' && inimigos[i].hp < inimigos[i].hpMax){
			inimigos[i].hp += 1;
			if(inimigos[i].hp > inimigos[i].hpMax) /*Não pode ter um HP maior que o Maximo*/
				inimigos[i].hp = inimigos[i].hpMax;
		}
		else if(inimigos[i].forma == 'M'){
			inimigos[i].hp += 2;
			if(inimigos[i].hp > inimigos[i].hpMax)
				inimigos[i].hp = inimigos[i].hpMax;
			if(inimigos[i].hp == inimigos[i].hpMax)
				inimigos[i].forma = 'V';
		}
	}
	x = dracula->posX + (rand()-rand())%2;
	y = dracula->posY + (rand()-rand())%2;
	if(mapa[1][y][x] == ' '){ /*Só moverá se estiver espaço vazio*/
		dracula->posX = x;
		dracula->posY = y;
	}
	/*O Dracula tem uma capacidade de regeneração maior, então quando
	 *Quando ele se move, são acrescentado 10 HP.
	 */
	dracula->hp += 10;
	if(dracula->hp > dracula->hpMax)
		dracula->hp = dracula->hpMax;
}

void imprimiStatusPlayer(vampiro *player, int numero_de_mortes){
	printf("nome: %s\n", player->nome);
	printf("LEVEL = %d\n", player->nivel);
	printf("XP = %d\n", player->xp);
	printf("HP = %d\n", player->hp);
	printf("atack = %d\n", player->atack);
	printf("lifeSteal = %d\n", player->life_steal);
	printf("pocoes = %d\n", (player->num_porcoes)-(player->porcoes_usadas));
	printf("precisao = %d\n", player->precisao);
	printf("numero de mortes = %d\n", numero_de_mortes);
	printf("press 'p' para pausar o jogo\n");
	printf("press '-' para sair do jogo\n");
}

int valorAbsoluto(int a){
	return(a > 0)?a:(-a);
}

int estaProximoParaEnfrentar(vampiro *player, vampiro *inimigo){
	int px = player->posX, py = player->posY, ix = inimigo->posX, iy = inimigo->posY;
	if(valorAbsoluto(px-ix) < 2 && valorAbsoluto(py-iy) < 2 && player->posZ == inimigo->posZ)
		return 1;
	return 0;
}

/*retorna o indice do inimigo, caso for o dracula retorna o numero de vampiros
 *(que é maior que o maior indice possivel) se não for enfrentar retorna -1*/
int enfrentarInimigo(vampiro *player, vampiro *inimigos, vampiro *dracula){
	int i = 0;
	if(player->posZ){
		if(estaProximoParaEnfrentar(player, dracula))
			return 12; /*12 é o numero de vampiros (sem contar o dracula)*/
	}
	while((!estaProximoParaEnfrentar(player, (inimigos+i)) && i < 12)|| (inimigos[i].forma == 'M')){
		i++;
	}
	return (i == 12)?-1:i;
}

void imprimeGameOver(){
	printf("%s%s\n\n\n", CSI, T_PURPLE);
	printf("\t\t\t\t\t\t ___              ___    ___        ___  __        A_A\n");
	printf("\t\t\t\t\t\t|      /\\  |\\  /||      |   |\\    /|    |  \\   /\\_/0 0\\_/\\\n");
	printf("\t\t\t\t\t\t| --; /__\\ | \\/ ||---   |   | \\  / |--- |__|  / ___'''___ \\\n");
	printf("\t\t\t\t\t\t|___|/    \\|    ||___   |___|  \\/  |___ |  \\  \\/   |||   \\/\n");
	printf("\n\n\n%s%s", CSI, T_WHITE);
}

void imprimeMensagemDaVitoria(){
	clrscrn();
	puts("\t\t\t\t\t\t ___                       ___  ___  .    __   ___  __  ___  _____       __  ___        ");
	puts("\t\t\t\t\t\t|   |  |\\  /|  /\\   |     |    |   | |   |  \\ |    |  ||   |   |    /\\  |  \\|   |  | | |");
	puts("\t\t\t\t\t\t|   |  | \\/ | /__\\  |     |--  |   | |   |  | |--  | < |   |   |   /__\\ |  ||   |  | | |");
	puts("\t\t\t\t\t\t|___|  |    |/    \\ |___  |    |___| |   |__/ |___ |  \\|___|   |  /    \\|__/|___|  o o o");
	puts("\t\t\t\t\t\t ___  ___  __    ___       ___                 _____  ___        A_A            A_A     ");
	puts("\t\t\t\t\t\t|   ||   ||  |  |    |\\  ||   ||   |  /\\  |\\  |  |   |   |   /\\_/0 0\\_/\\    /\\_/0 0\\_/\\ ");
	puts("\t\t\t\t\t\t|---'|   || <   |--  | \\ ||   ||   | /__\\ | \\ |  |   |   |  / ___'''___ \\  / ___'''___ \\");
	puts("\t\t\t\t\t\t|    |___||  \\  |___ |  \\||___\\|___|/    \\|  \\|  |   |___|  \\/   |||   \\/  \\/   |||   \\/");
	puts("\t\t\t\t\t\tpress enter");
	limpaBuffer();
}

/*a variavel indice é o indice do vampiro derotado*/
void abrirPorta(int indice, char mapa[3][130][130]){
	if(indice < 4)
		mapa[0][23][32+(16*(indice%4))] = '-';
	else
		mapa[0][15][16*(4-(indice%4))] = '-';
}

/*Essa função serve tanto para iniciar o mapa quanto para re-iniciar*/
void iniciaMapa(char mapaInicial[3][130][130], char mapa[3][130][130]){
	int i, j, k;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 130; j++)
			for(k = 0; k < 130; k++)
				mapa[i][j][k] = mapaInicial[i][j][k];
}

void restartPlayer(vampiro *player){
	/*player->nivel = 1*/ /* <<-- Se querer um pouco mais de emoção retire o comentario dessa parte*/
	player->hpMax = 48 + 2*(player->nivel);
	player->hp = player->hpMax;
	player->atack = 6 + (player->nivel)/2;
	player->life_steal = (player->nivel)/3;
	player->precisao = 55 + 2*(player->nivel);
	player->num_porcoes = 0;
	player->porcoes_usadas = 0;
	player->atordoado = 'N';
	player->forma = '@';
	player->xp = 0;
}

/*função usada para aumentar o nivel do jogador
 *Note que esta aparescendo nos termos a expressão
 *1+player->nivel, isso pois só entra nessa condicional se
 *ele aumentar de nivel.
 */
void setStatosPlayer(vampiro *player){
	if(player->xp >= 2*(player->nivel)){ /*sobe de nivel se o xp > 2*nivel_atual*/
		if(player->atack > (6 + ((player->nivel)/2))){ /*  <<-- essa condicional ao lado indica se o player tem ou não um item*/
			player->atack = (6 + ((1+player->nivel)/2)) +6; /* <<-- +6 pois ele tem uma Arma (unica variavel que deve ser diferente do esperado)*/
			player->life_steal = (1+player->nivel)/3;
			player->precisao = 55 + 2*(1+player->nivel);
		}
		else if(player->atack < (6 + ((player->nivel)/2))){ /*<<-- nessa condição o player tem uma armadura*/
			player->atack = (6 + (1+player->nivel)/2) - 2; /* <<-- -2 pois ele tem uma armadura*/
			player->life_steal = ((1+player->nivel)/3) + 10;  /*aumenta o life_steal em 10*/
			player->precisao = (55 + 2*(1+player->nivel)) + 15;    /*aumenta a precisão em 15*/
		}
		else{  /*<<-- esse ultimo else indica que nosso jogador esta sem itens*/
			player->atack = (6 + ((1+player->nivel)/2));
			player->life_steal = (1+player->nivel)/3;
			player->precisao = 55 + 2*(1+player->nivel);
		}
		/*precisão de mais de 100% é desnecessario*/
		if(player->precisao > 100)
			player->precisao = 100;
		player->hpMax = 48 + 2*(1+player->nivel);
		player->atordoado = 'N';
		player->xp = (player->xp) - (2*player->nivel);
		player->nivel += 1;
	}
}

void restartGameConditions(char mapaInicial[3][130][130], char mapa[3][130][130], vampiro *player, vampiro *inimigos, vampiro *dracula, int *numero_de_itens_no_mapa){
	restartPlayer(player);
	iniciaPosPlayer(player);
	iniciaMapa(mapaInicial, mapa);
	iniciaInimigo(inimigos, dracula);
	*numero_de_itens_no_mapa = 5;
}

int main(){
	char mapaInicial[3][130][130] ={
		{{"#####################################################################################"},
	     {"#      P        #       P       #      W        #      A        #      T        #   #"}, /*T = teletransporte*/
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"######   ##############   ############   #############   #############   ########   #"},
	     {"#######-################-##############-###############-############### #########   #"},
	     {"#                                                                               #   #"},
	     {"#-###############################################################################   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#      P        +               +               +               +               -   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"}, /*T = teletransporte*/
	     {"#################################################################################   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               -               +               +               +               +   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#               #               #               #               #               #   #"},
	     {"#####################################################################################"}},

		  {{"#####################################################################################"},
		   {"#               W                P        ###########################################"},
		   {"#         ##############################  ###########################################"},
		   {"#         ##############################  ###########################################"},
		   {"#       T ##############################  ###########################################"},
		   {"#         ##############################||###########################################"},
		   {"#  #####################################\\/###########################################"},
		   {"#  ########################                               ###########################"},
		   {"#  ########################                               ###########################"},
		   {"#  ########################                               ###########################"},
		   {"#  ########################                               ###########################"},
		   {"#  ########################                               ###########################"},
		   {"#  ########################                               ###########################"},
		   {"#  ########################                               ###########################"},
		   {"#    A             P     ->                               ###########################"},
		   {"###########################                               ###########################"},
		   {"###########################                               ###########################"},
		   {"###########################                               ###########################"},
		   {"###########################                               ###########################"},
		   {"###########################                               ###########################"},
		   {"#####################################################################################"},
		   {"#####################################################################################"},
		   {"#####################################################################################"},
		   {"#####################################################################################"},
		   {"####################################DRACULA!#########################################"},
		   {"#####################################################################################"},
		   {"#####################################################################################"},
		   {"#####################################################################################"}}};
	char mapa[3][130][130];
	vampiro player, inimigos[12], dracula;
	int numero_de_mortes = 0; /*se o numero de mortes > 5, game over*/
	int numero_de_itens_no_mapa = 5; /*numero de itens no mapa[0][][]*/
	int usleep(int);
	int indice, resultOfGame;
	iniciaMapa(mapaInicial, mapa);
	iniciaPlayer(&player);
	iniciaInimigo(inimigos, &dracula);
	char dir; /*direção*/
	while(1){
		while(!kbhit()) {
			clrscrn();
			indice = -1;
			imprimiMap(mapa, &player, inimigos, &dracula);
			imprimiStatusPlayer(&player, numero_de_mortes);
			indice = enfrentarInimigo(&player, inimigos, &dracula);
			if(indice < 12 && indice > -1){
				limpaBufferComKbhit();
				resultOfGame = playGame(&player, (inimigos+indice));
				if(resultOfGame == 1){
					inimigos[indice].forma = 'M';
					abrirPorta(indice, mapa);
					setStatosPlayer(&player);
				}
				else{
					if(resultOfGame == -1){
						numero_de_mortes++;
						restartGameConditions(mapaInicial, mapa, &player, inimigos, &dracula, &numero_de_itens_no_mapa);
					}
					if(numero_de_mortes > 5){
						imprimeGameOver();
						return 0;
					}
					iniciaPosPlayer(&player);
				}
			}
			else if(indice == 12){
				limpaBufferComKbhit();
				resultOfGame =  playGame(&player, &dracula);
				if(resultOfGame == 1){
					/*Todas as vezes que o Dracula perde
					 *Ele treina mais e aumenta sua forca
					 */
					dracula.hpMax += 20;
					dracula.hp = dracula.hpMax;
					dracula.atack += 5;
					dracula.precisao += 10;
					setStatosPlayer(&player);
					imprimeMensagemDaVitoria();
					iniciaPosPlayer(&player);
				}
				else{
					if(resultOfGame == -1){
						numero_de_mortes++;
						restartGameConditions(mapaInicial, mapa, &player, inimigos, &dracula, &numero_de_itens_no_mapa);
					}
					if(numero_de_mortes > 5){
						imprimeGameOver();
						return 0;
					}
					iniciaPosPlayer(&player);
				}
			}
			usleep(100000);
			moveInimigos(inimigos, &dracula, mapa);
		}
		do{
			dir = getch();
			limpaBufferComKbhit();
			if(dir == '-') /*o caracter '-' é usando nesse jogo para sair do mesmo*/
				return 0;
			puts("\npress any button != 'p' && != '-' para continuar");
		}while(dir == 'p' && dir != 'a' && dir != 's' && dir != 'd' && dir != 'w'); /*p = pause*/
		movePlayer(&player, dir, mapa);
		setItemPlayer(&player, mapa, &numero_de_itens_no_mapa);
	}
	return 0;
}
