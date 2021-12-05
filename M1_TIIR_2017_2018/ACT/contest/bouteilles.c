#include <stdio.h>
#include <stdlib.h>

static int** matrix = NULL;

int max (int a, int b) {
    if (a>b)
        return a;
    return b;
}

int dyn_rec(int tab[], int y, int g, int d) {

    if (g == d) {
        if (matrix[g][g] == 0) {
            matrix[d][d] = y * tab[g];
        }
        return matrix[g][g];
    }

    if (matrix[g][d] == 0) {
        matrix[g][d] = max((tab[g] * y + dyn_rec(tab, y + 1, g + 1, d)), (tab[d] * y + dyn_rec(tab, y + 1, g,d - 1)));
    }

    return matrix[g][d];
}

void display(int* tab, int n) {
    int x;
    int i = 0;
    int j = n - 1;
    int tmpG,tmpD;
    int cond1,cond2;
    int g = 0;
    int d = n-1;
    for (int y = 1; g!=d; y++) {

        x = matrix[i][j];
        tmpG = matrix[i][j-1];
        tmpD = matrix[i+1][j];

        cond1 = (x == (tmpD + (y * tab[g]))) || (x == (tmpG + (y * tab[g])));
        cond2 = (x == (tmpD + (y * tab[d]))) || (x == (tmpG + (y * tab[d])));

        if (cond1) {
            printf("%d ",tab[g]);
            i++;
            g++;
        }
        if (cond2) {
            printf("%d ",tab[d]);
            d--;
            j--;
        }

    }

    printf("%d \n",tab[g]);
}

int main() {

    int n;
    scanf("%d",&n);

    int* tab = malloc(sizeof(int)*n);

    matrix = (int **)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) matrix[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        scanf("%d",&tab[i]);
    }

    dyn_rec(tab, 1, 0, n - 1);

    printf("%d\n",matrix[0][n-1]);

    display(tab,n);

    return 0;
}