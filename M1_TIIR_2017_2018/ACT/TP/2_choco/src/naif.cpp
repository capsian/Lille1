#include <iostream>
using namespace std;

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

    int sav[m+n];
    int k = 0;
    if ((m == 1) && (n == 1)) {
        return 0;
    }

    //On coupe à gauche
    for (int l=1;l<=i;l++) {
        sav[k++] = f(m-l, n, i-l, j);
    }

    //On coupe en haut
    for (int l=1;l<=j;l++) {
        sav[k++] = f(m, n-l, i, j-l);
    }

    //On coupe à droite
    for (int l=1;l<(m-i);l++) {
        sav[k++] = f(m-l, n, i, j);
    }

    //On coupe en bas
    for (int l=1;l<(n-j);l++) {
        sav[k++] = f(m, n-l, i, j);
    }

    return score(sav,k);
}


int main() {

    int m,n,i,j;

    cin >> m >> n >> i >> j;

    cout << f(m,n,i,j) << endl;

    return 0;
}
