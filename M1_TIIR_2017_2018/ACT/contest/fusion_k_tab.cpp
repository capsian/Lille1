#include <iostream>
#include <cstdlib>
#include <list>
using namespace std;

bool mycomparison (int a, int b) {
    return a < b;
}

int main() {

    int nbTab;
    int nbElem;
    list<int> tmp;
    list<int> res;
    int x;

    cin >> nbTab >> nbElem;
    int matrix[nbTab][nbElem];

    for (int i=0; i<nbTab; i++) {

        for (int j = 0; j < nbElem; j++) {

            if (!i) {
                cin >> x;
                res.push_back(x);
                //cout << "F";
            } else {
                cin >> x;
                tmp.push_back(x);
            }
        }
        //cout << endl;

        if (i) {
            res.merge(tmp,mycomparison);
        }

    }

    for (list<int>::iterator it=res.begin(); it != res.end(); ++it)
        cout << ' ' << *it;
    cout << endl;

    return 0;
}