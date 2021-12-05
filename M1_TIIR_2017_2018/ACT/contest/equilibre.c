//
// Created by worker on 16/09/17.
//

#include "stdio.h"
#include "stdlib.h"
#include <math.h>

void try1() {
    int cpt0 = 0;
    int cpt1 = 0;
    int max = 0;
    int* tab = NULL;
    int n = 0;

    scanf("%d",&n);
    tab = malloc(sizeof(int) * n);

    for (int i=0; i<n; i++) {
        scanf("%d",&tab[i]);
    }

    for (int i=0; i<n; i++) {

        if (tab[i] == 0) { cpt0++; }
        else             { cpt1--; }
    }

    printf(" cpt0 (+) = %d, cpt1 (-) = %d\n",cpt0,cpt1);

    if (fabs(cpt0) > fabs(cpt1)) {
        max =  fabs(cpt1) * 2;
    } else {
        max =  fabs(cpt0) * 2;
    }

    printf("%d\n",max);
}

void try2() {

    int* tab = NULL;
    int n = 0;

    scanf("%d",&n);
    tab = malloc(sizeof(int) * n);

    for (int i=0; i<n; i++) {
        scanf("%d",&tab[i]);
    }

    int last = tab[0];
    int cptNEQ = 0;
    int cptEQ = 0;
    int sw = 0;
    int max = 0;
    int MAX = 0;

    for (int i=1; i<n; i++) {
        printf("try2() intération tab[%d] = %d \n",i,tab[i]);
        if ((tab[i] != last) && (sw) ){
            cptNEQ++;
            sw++;
            printf(" if != | cptNEQ = %d \n",cptNEQ);
        }
        else {
            cptEQ++;
            printf(" else | cptEQ = %d \n",cptEQ);
        }

        if (sw > 1) {

            if (cptEQ > cptNEQ) { max = cptNEQ; } else { max = cptEQ; }
            if (MAX < max) { MAX = max;}

            printf(" SWITCHED ! | cptEQ = %d, cptNEQ = %d, max = %d, MAX = %d\n",cptEQ,cptNEQ,max,MAX);
            sw = 0;
        }

        last = tab[i];
    }

    printf("%d\n",max);
}

void try3 () {
    int* tab = NULL;
    int n = 0;

    scanf("%d",&n);
    tab = malloc(sizeof(int) * n);

    for (int i=0; i<n; i++) {
        scanf("%d",&tab[i]);
    }

    int balance = 0;
    int cpt0 = 0, cpt1 = 0;
    int MAX = 0;

    for (int i = 0; i < n; i++) {
        if (tab[i] == 0) {
            balance--;
            cpt0++;
        } else {
            balance++;
            cpt1++;
        }

        if (balance == 0) {
            MAX = i + 1;
        }
    }

    if (MAX == 0) {
        if (cpt0 > cpt1) {
            MAX = cpt1 * 2;
        } else {
            MAX = cpt0 * 2;
        }
    }

    printf("%d\n",MAX);
}

int main() {

    try3();

    return 0;
}