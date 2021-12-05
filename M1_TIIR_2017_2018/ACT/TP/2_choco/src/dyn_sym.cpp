#include <iostream>
#include <stdlib.h>

using namespace std;
int *cube;
int width, height, depth, other_dimension;

int get_element(int m, int n, int i, int j) {

    if (m < width && n < height && i < depth && j < other_dimension) {
        return cube[(j * width * height * depth) + (i * width * height) + (n * width) + m];
    } else {
        return 0;
    }
}

void set_element(int m, int n, int i, int j, int value) {

    if (m < width && n < height && i < depth && j < other_dimension) {
        cube[(j * width * height * depth) + (i * width * height) + (n * width) + m] = value;
    }
}

int score(int *sav, int n) {

    int maxNeg = sav[0];
    char isNeg = 0;
    int maxPos = sav[0];

    for (int i = 0; i < n; i++) {
        if (sav[i] <= 0) {
            isNeg = 1;
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

void symetrie(int m, int n, int i, int j) {

    int tmp_cube_elem = get_element(m, n, i, j);

    //CAS 1
    set_element(n, m, j, i, tmp_cube_elem);

    //CAS 2 et 3
    set_element(m, n, (m - 1) - i, j, tmp_cube_elem);
    set_element(n, m, j, (m - 1) - i, tmp_cube_elem);

    //Cas 4 et 5
    set_element(m, n, i, (n - 1) - j, tmp_cube_elem);
    set_element(n, m, (n - 1) - j, i, tmp_cube_elem);

    //Cas 6 et 7
    set_element(m, n, (m - 1) - i, (n - 1) - j, tmp_cube_elem);
    set_element(n, m, (n - 1) - j, (m - 1) - i, tmp_cube_elem);
}

int f(int m, int n, int i, int j) {

    //cout << " enter with m = " << m << " n = " << n << " i = " << i << " j = " << j << endl;

    int sav[n + m];
    int k = 0;
    if ((m == 1) && (n == 1)) {
        //cout << " cas de base " << endl;
        return 0;
    }

    //On coupe à gauche
    for (int l = 1; l <= i; l++) {
        //cout << "f(" << m-l << "," << n << "," << i-l << "," << j << ")" << endl;
        int tmp;
        if ((tmp = get_element(m - l, n, i - l, j)) == 0) {
            tmp = f(m - l, n, i - l, j);
            set_element(m - l, n, i - l, j, tmp);
            symetrie(m - l, n, i - l, j);
        }
        sav[k++] = tmp;
    }

    //On coupe en haut
    for (int l = 1; l <= j; l++) {
        //cout << "f(" << m << "," << n-l << "," << i << "," << j-l << ")" << endl;
        int tmp;
        if ((tmp = get_element(m, n - l, i, j - l)) == 0) {
            tmp = f(m, n - l, i, j - l);
            set_element(m, n - l, i, j - l, tmp);
            symetrie(m, n - l, i, j - l);
        }
        sav[k++] = tmp;
    }

    //On coupe à droite
    for (int l = 1; l < (m - i); l++) {
        //cout << "f(" << m-l << "," << n << "," << i << "," << j << ")" << endl;
        int tmp;
        if ((tmp = get_element(m - l, n, i, j)) == 0) {
            tmp = f(m - l, n, i, j);
            set_element(m - l, n, i, j, tmp);
            symetrie(m - l, n, i, j);
        }
        sav[k++] = tmp;
    }

    //On coupe en bas
    for (int l = 1; l < (n - j); l++) {
        //cout << "f(" << m << "," << n-l << "," << i << "," << j << ")" << endl;
        int tmp;
        if ((tmp = get_element(m, n - l, i, j)) == 0) {
            tmp = f(m, n - l, i, j);
            set_element(m, n - l, i, j, tmp);
            symetrie(m, n - l, i, j);
        }
        sav[k++] = tmp;
    }

    return score(sav, k);
}


int main() {
    int m, n, i, j;
    cin >> m >> n >> i >> j;

    width = m + 1;
    height = n + 1;
    depth = i + 1;
    other_dimension = j + 1;

    cube = (int *) malloc(sizeof(int) * width * height * depth * other_dimension);

    cout << f(m, n, i, j) << endl;

    free(cube);

    return 0;
}
