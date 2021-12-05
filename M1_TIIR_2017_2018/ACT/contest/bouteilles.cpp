#include <iostream>

using namespace std;

int dyn_rec(int tab[], int y, int g, int d, int matrix[][d]) {

    if (g == d) {
        if (matrix[g][g] != 0) {
            matrix[d][d] = y * tab[g];
        }
        return matrix[g][g];
    }

    if (matrix[g][d] != 0) {
        matrix[g][d] = max((tab[g] * y + dyn_rec(tab, y + 1, g + 1, d,matrix)), (tab[g] * y + dyn_rec(tab, y + 1, g,d - 1,matrix)));
    }
    return matrix[g][d];
}


int main() {

    int n;
    cin >> n;

    int tab[n];
    int matrix[n][n];

    for (int i = 0; i < n; ++i) {
        cin >> tab[i];
    }

    dyn_rec(tab, 1, 0, n - 1,matrix);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}