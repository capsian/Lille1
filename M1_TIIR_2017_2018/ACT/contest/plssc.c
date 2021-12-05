#include <stdio.h>
#include <stdlib.h>


struct node {
    int pos;
    int pred;
};
typedef struct node node;

static node* rTab = NULL;

node constructNode(int* tab, int pos) {

    printf("constructNode enter with pos = %d , elem = %d\n",pos,tab[pos]);

    node nd;
    int k = 0;
    int elem = tab[pos];
    int tabPosInf[pos+1];   tabPosInf[0] = -1;

    for (int i = 0; i < pos; i++) {
        if (tab[i] < elem) {
            tabPosInf[k] = i+1;
            k++;
        }

    }

    if (tabPosInf[0] == -1) {
        nd.pred = 1;
        nd.pos = 0;
        printf("constructNode exit1 with pos = %d, pred = %d\n",nd.pos, nd.pred);
        return nd;
    }

    for (int i = 0; i < pos; i++) {
        printf(" tabPosInf[%d] = %d | ",i,tabPosInf[i]);
    }
    printf("\n");

    int tmpPos = tabPosInf[0];
    int savPos = tmpPos;
    int max = -1;

    for (int i = 1; i < k; i++) {

        tmpPos = tabPosInf[i];

        if (max < rTab[tmpPos].pred) {
            max = rTab[tmpPos].pred;
            savPos = i;
        }
    }

    nd.pos = savPos;
    nd.pred = rTab[savPos].pred + 1;

    printf("constructNode exit2 with pos = %d, pred = %d\n",nd.pos, nd.pred);
    return nd;
}

int main() {

    int n;
    int* tab = NULL;
    scanf("%d",&n);
    tab = malloc(sizeof(int) * n);
    rTab = malloc(sizeof(node) * n + 1);

    for (int i = 0; i < n; ++i) {
        scanf("%d",&tab[i]);
    }

    int max = -1;
    rTab[0].pos = 0;
    rTab[0].pred = 0;
    for (int i = 0; i < n; i++) {

        rTab[i+1] = constructNode(tab,i);

        if ( max < rTab[i+1].pred)
            max = rTab[i+1].pred;
    }

    printf("%d\n",max);

    for (int i = 0; i < n+1; i++) {
        printf(" pos = %d, pred = %d | ",rTab[i].pos, rTab[i].pred);
    }
    printf("\n");

    return 0;
}