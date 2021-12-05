#include <stdio.h>
#include <stdlib.h>

static int odd = 0;     // hold last index

void rot(int* t, int n) {

    int tmp = t[n-1];

    for(int i=(n-1); i > 1; i--) {
        t[i] = t[i-1];
    }

    t[1]= tmp;
}

void display(int* t, int n) {

    if (odd) {
        int j = n-1;
        for (int i=0; i<n/2; i++, j--) {
            if ((t[i] != odd) && (t[j] != odd))
                printf("%d %d ",t[i],t[j]);
        }

    } else {
        int j = n-1;
        for (int i=0; i<n/2; i++, j--) {
            printf("%d %d ",t[i],t[j]);
        }

    }
    printf("\n");
}

void try1() {

    int n = 0;

    scanf("%d",&n);

    // todo: fixme !!
    if (n == 2) {
        printf("(1 - 2)\n");
        return;
    }

    if (n % 2 != 0) {
        odd = ++n;
    }

    // init
    int* tab  = malloc(sizeof(int) * n);
    for (int i=0; i<n; i++) { tab[i] = (i+1);}

    for (int i=0; i<n-1; i++) {
        display(tab,n);
        rot(tab,n);
    }

}

int main() {

    try1();

    return 0;
}