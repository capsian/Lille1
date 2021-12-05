#include "stdio.h"
#include "stdlib.h"

void try1() {

    int n = 0;

    scanf("%d",&n);
    int* tab  = malloc(sizeof(int) * n);
    int* tab1 = malloc(sizeof(int) * n);
    int* tab2 = malloc(sizeof(int) * n);

    for (int i=1; i<=n; i++) {
        scanf("%d",&tab[i]);
        tab1[i] = -1;
        tab2[i] = -1;
    }

    tab1[1] = tab[1];
    int i = 1;
    int j = 0;
    for (int k = 2; k<=n; k++) {

        if (tab[k] == tab1[i]) {
            tab1[i+1] = tab[k];
            i++;
        } else {
            if (j == 0) {

                tab2[j+1] = tab[k];
                j++;
            } else {

                if (tab2[j] != tab[k]) {

                    tab1[i+1] = tab2[j];
                    tab1[i+2] = tab[k];
                    i += 2;
                    j--;
                } else {
                    tab2[j+1] = tab[k];
                    j++;
                }
            }
        }
    }

    int x = -1;
    if (j>1) {
        x = tab2[1];
    } else {
        x = tab1[1];
    }

    int cpt = 0;
    for (int i = 0; i<n; i++) {
        if ( tab[i] == x) {
            cpt++;
        }
    }

    if (cpt >= ((n/2) + 1)) {
        printf("%d\n",x);
    }

}

int contains(int val, int* tab, int n) {

    for (int i=0; i<n; i++) {
        if (tab[i] == val)
            return 1;
    }

    return 0;
}

int isMajor(int val, int* tab, int n) {

    int cpt = 0;

    for( int i=0; i<n; i++) {

        if (tab[i] == val)    {cpt++; }
        if (cpt == (n/2) + 1) { return 1;}
    }

    return 0;
}

void try2() {

    int n = 0;

    scanf("%d",&n);
    int* tab  = malloc(sizeof(int) * n);
    int* dup = malloc(sizeof(int) * n);     /* todo: check limit */

    // input
    for (int i=0; i<=n; i++) {
        scanf("%d",&tab[i]);
        dup[i] = -1;
    }

    // check if there is 2 succ val
    // put it in dup[]
    int j = 0;
    for (int i=0; i<n; i++) {

        if (tab[i] == tab[i+1]) {
            if (!contains(tab[i],dup,j)) {
                dup[j] = tab[i];
                j++;
                i++;
            }
        }
    }

    int x = -1;
    for (int i=0; i<j; i++) {
        if (isMajor(dup[i],tab,n)) {        // count(dup[i]) >= (n/2)+1
            x = dup[i];
            break;
        }
    }

    printf("%d\n",x);
}


int main() {

    try2();

    return 0;
}