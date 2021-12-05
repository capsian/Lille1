#include <iostream>
#define MAX_SIZE 200

using namespace std;
static int cube[MAX_SIZE][MAX_SIZE][MAX_SIZE][MAX_SIZE];

int score (int* sav, int n) {

    int maxNeg = sav[0];
    int isNeg = 0;
    int maxPos = sav[0];

    for (int i = 0; i < n; i++) {
        if (sav[i] <= 0) {
            isNeg++;
            if (maxNeg > sav[i]) {
                maxNeg = sav[i];
            }
        } else {
            if (maxPos < sav[i]) {
                maxPos = sav[i];
            }
        }
    }

    if (isNeg) {
        return (maxNeg * -1) + 1;
    } else {
        return (maxPos * -1) - 1;
    }

}

int f(int m, int n, int i, int j) {

    //cout << " enter with m = " << m << " n = " << n << " i = " << i << " j = " << j << endl;

    int sav[n+m];
    int k = 0;
    if ((m == 1) && (n == 1)) {
        //cout << " cas de base " << endl;
        return 0;
    }

    //On coupe à gauche
    for (int l=1;l<=i;l++) {
        //cout << "f(" << m-l << "," << n << "," << i-l << "," << j << ")" << endl;
        if (cube[m-l][n][i-l][j] == 0){
            cube[m-l][n][i-l][j] = f(m-l, n, i-l, j);

        }
        sav[k++] = cube[m-l][n][i-l][j];
    }

    //On coupe en haut
    for (int l=1;l<=j;l++) {
        //cout << "f(" << m << "," << n-l << "," << i << "," << j-l << ")" << endl;
        if (cube[m][n-l][i][j-l] == 0){
            cube[m][n-l][i][j-l] = f(m, n-l, i, j-l);

        }
        sav[k++] = cube[m][n-l][i][j-l];
    }

    //On coupe à droite
    for (int l=1;l<(m-i);l++) {
        //cout << "f(" << m-l << "," << n << "," << i << "," << j << ")" << endl;
        if (cube[m-l][n][i][j] == 0){
            cube[m-l][n][i][j] = f(m-l, n, i, j);

        }
        sav[k++] = cube[m-l][n][i][j];
    }

    //On coupe en bas
    for (int l=1;l<(n-j);l++) {
        //cout << "f(" << m << "," << n-l << "," << i << "," << j << ")" << endl;
        if (cube[m][n-l][i][j] == 0){
            cube[m][n-l][i][j] = f(m, n-l, i, j);

        }
        sav[k++] = cube[m][n-l][i][j];
    }

    return score(sav,k);
}


int main() {

    cout << f(127,127,63,126) << endl;
    return 0;
}
