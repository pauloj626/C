/*
    Ad-hoc 2567 - Virus
*/

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main(void) {
    int v[1000];
    int t,i,s;
    while(scanf("%d",&t) != EOF) {
        for (i = 0; i < t; i++) {
            scanf("%d",&v[i]);
        }
        qsort(v,t,sizeof(int),cmp);
        t--;
        for (s = 0, i = 0; i < t; t--, i++) {
            s += abs(v[t]-v[i]);
        }
        printf("%d\n",s);
    }
    return 0;
}
