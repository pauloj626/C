/*
    Ad-hoc 2051 - Mapas de Karnaugh I
*/

#include <stdio.h>
#include <string.h>

int zeroCount(int *v,int n) {
	int i;
	int c;
	for (i = 0, c = 0; i < n; i++) {
		if (!v[i]) c++;
	}
	return c;
}

void printKarnaugh2(int *v) {
	puts("Mapa de Karnaugh");
	puts("  0 1");
	printf("0|%d %d\n",v[0],v[2]);
	printf("1|%d %d\n",v[1],v[3]);
	if (!zeroCount(v,4)) puts("Tautologia");
	else if (zeroCount(v,4) == 4) puts("Contradicao");
	else puts("Contingencia");
}

void printKarnaugh3(int *v) {
	puts("Mapa de Karnaugh");
	puts("  00 01 11 10");
	printf("0|%d  %d  %d  %d\n",v[0],v[2],v[6],v[4]);
	printf("1|%d  %d  %d  %d\n",v[1],v[3],v[7],v[5]);
	if (!zeroCount(v,8)) puts("Tautologia");
	else if (zeroCount(v,8) == 8) puts("Contradicao");
	else puts("Contingencia");
}

void printKarnaugh4(int *v) {
	puts("Mapa de Karnaugh");
	puts("   00 01 11 10");
	printf("00|%d  %d  %d  %d\n",v[0],v[4],v[12],v[8]);
	printf("01|%d  %d  %d  %d\n",v[1],v[5],v[13],v[9]);
	printf("11|%d  %d  %d  %d\n",v[3],v[7],v[15],v[11]);
	printf("10|%d  %d  %d  %d\n",v[2],v[6],v[14],v[10]);
	if (!zeroCount(v,16)) puts("Tautologia");
	else if (zeroCount(v,16) == 16) puts("Contradicao");
	else puts("Contingencia");
}

int main(void) {
	int N,V,v[16];
	int a,b,c,d,e,i;
	char fst = 1;
	scanf("%d",&N);
	while (N--) {
		if (!fst) puts("");
		fst = 0;
		memset(v,0,sizeof(v));
		scanf("%d",&V);
		if (V == 2) {
			for (i = 0; i < 4; i++) {
				scanf("%d %d - %d",&a,&b,&e);
				v[b + (a << 1)] = e;
			}
		}
		else if (V == 3) {
			for (i = 0; i < 8; i++) {
				scanf("%d %d %d - %d",&a,&b,&c,&e);
				v[c + (b << 1) + (a << 2)] = e;
			}
		}
		else {
			for (i = 0; i < 16; i++) {
				scanf("%d %d %d %d - %d",&a,&b,&c,&d,&e);
				v[d + (c << 1) + (b << 2) + (a << 3)] = e;
			}
		}

		if (V == 2) printKarnaugh2(v);
		else if (V == 3) printKarnaugh3(v);
		else printKarnaugh4(v);
	}
	return 0;
}
