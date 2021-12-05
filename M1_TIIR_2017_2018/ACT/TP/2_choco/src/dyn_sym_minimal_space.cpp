#include <iostream>
#include <stdlib.h>
using namespace std;

int* cube;
int  w ,h , d ,o;

void display_space(int* minim_space_config) {
    cout << "minimal space :m = " << minim_space_config[0] << ", n = " << minim_space_config[1] << ", i = " << minim_space_config[2] << ", j = " << minim_space_config[3] << endl;
}

void get_minimal_space_config(int m, int n, int i, int j, int* minim_space_config) {

  int I,J,minI,minJ;
  int tmp;
  I = m - 1 - i ;
  J = n - 1 - j;
  minI = min(i,I);
  minJ = min(j,J);
  if ( n > m && minJ == minI){
    minim_space_config[0] = n;
    minim_space_config[1] = m;
    minim_space_config[2] = minJ;
    minim_space_config[3] = minI;
  }else if (minJ > minI) {
    minim_space_config[0] = n;
    minim_space_config[1] = m;
    minim_space_config[2] = minJ;
    minim_space_config[3] = minI;
  }

  else{
    minim_space_config[0] = m;
    minim_space_config[1] = n;
    minim_space_config[2] = minI;
    minim_space_config[3] = minJ;
  }
    // if (m == n) {
    //     int tmpI = i;
    //     i = max(i,j);
    //     j = min(tmpI,j);
    // }
    //
    // if (n > m) {
    //     if (j>i) {
    //
    //         int tmp = m;
    //         m = n;
    //         n = tmp;
    //
    //         tmp = i;
    //         i = j;
    //         j = tmp;
    //     }
    // }
    //
    // minim_space_config[0] = m;
    // minim_space_config[1] = n;
    //
    // // plus petite symetrie
    // if ((m - i - 1) < i)
    //     minim_space_config[2] = m - i - 1;
    // else
    //     minim_space_config[2] = i;
    //
    // if ((n - j - 1) < j)
    //     minim_space_config[3] = n - j - 1;
    // else
    //     minim_space_config[3] = j;
    //
    //     int tmpI = minim_space_config[2];
    //     minim_space_config[2] = max(tmpI,minim_space_config[3]);
    //     minim_space_config[3] = min(tmpI,minim_space_config[3]);

}


int get_element(int m, int n, int i, int j) {

    return cube[(j * w * h * d) + (i * w * h) + (n * w) + m];
}

void set_element(int m, int n, int i, int j,int value) {

    cube[(j * w * h * d) + (i * w * h) + (n * w) + m] = value;
}

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

    int sav[n+m];
    int k = 0;

    if ((m == 1) && (n == 1)) {
        //cout << " cas de base " << endl;
        return 0;
    }
    //On coupe à gauche
    for (int l=1;l<=i;l++) {
        //cout << "f(" << m-l << "," << n << "," << i-l << "," << j << ")";
        int tmp;
        int minim_space_config_new[4];
        get_minimal_space_config(m-l,n,i-l,j,minim_space_config_new);
        //display_space(minim_space_config_new);

        if ((tmp = get_element(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3])) == 0) {

            tmp = f(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3]);
            set_element(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3],tmp);
        }
        sav[k++] = tmp;
    }

    //On coupe en haut
    for (int l=1;l<=j;l++) {
        //cout << "f(" << m << "," << n-l << "," << i << "," << j-l << ")" << endl;
        int tmp;
        int minim_space_config_new[4];
        get_minimal_space_config(m,n-l,i,j-l,minim_space_config_new);
        //display_space(minim_space_config_new);

        if ((tmp = get_element(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3])) == 0) {

            tmp = f(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3]);
            set_element(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3],tmp);
        }

        sav[k++] = tmp;
    }

    //On coupe à droite
    for (int l=1;l<(m-i);l++) {
        //cout << "f(" << m-l << "," << n << "," << i << "," << j << ")" << endl;
        int tmp;
        int minim_space_config_new[4];
        get_minimal_space_config(m-l,n,i,j,minim_space_config_new);
        //display_space(minim_space_config_new);

        if ((tmp = get_element(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3])) == 0) {

            tmp = f(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3]);
            set_element(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3],tmp);
        }

        sav[k++] = tmp;
    }

    //On coupe en bas
    for (int l=1;l<(n-j);l++) {
        //cout << "f(" << m << "," << n-l << "," << i << "," << j << ")" << endl;
        int tmp;
        int minim_space_config_new[4];
        get_minimal_space_config(m,n-l,i,j,minim_space_config_new);
        //display_space(minim_space_config_new);

        if ((tmp = get_element(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3])) == 0) {

            tmp = f(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3]);
            set_element(minim_space_config_new[0],minim_space_config_new[1],minim_space_config_new[2],minim_space_config_new[3],tmp);
        }

        sav[k++] = tmp;
    }

    return score(sav,k);
}


int main() {
    int m,n,i,j;
    cin >> m >> n >> i >> j;

    int minim_space_config[4];
    get_minimal_space_config(m,n,i,j,minim_space_config);
  //  display_space(minim_space_config);

    w = minim_space_config[0];
    h = minim_space_config[1];
    d = minim_space_config[2];
    o = minim_space_config[3];

    cube = (int *) malloc(sizeof(int) * minim_space_config[0] * minim_space_config[1] * (minim_space_config[2]+1) * (minim_space_config[3]+1) );

    cout << f(minim_space_config[0],minim_space_config[1],minim_space_config[2],minim_space_config[3]) << endl;

    free(cube);

    return 0;
}