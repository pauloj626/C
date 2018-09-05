#include <stdio.h>
#include <stdlib.h>

float IEEE754_32(){
	char str[40];
	int i, num = 0;
	scanf("%s", str);
	for(i = 0; i < 32; i++)
		num = num | ((str[i] - '0') << (31 - i));
	return *(float *) &num; 
}

int main(){
	printf("Digite n: ");
	printf("%.2f\n", IEEE754_32());
	return 0;
}