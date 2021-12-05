#include <iostream>
#include <list>

using namespace std;

typedef struct Point {
    int x;
    int y;
}Point;

static list<Point> out;
static list<Point> LAST_INIT;

void init() {
    Point p;

    p.y = -1; p.x = -1;
    LAST_INIT.push_front(p);
    out.push_front(p);

    return;
}

list<Point>::iterator insertP1(Point newP) {

    list<Point>::iterator res;

    list<Point>::iterator lastIt = LAST_INIT.begin();
    list<Point>::iterator pntIt;

    for (pntIt = out.begin(); pntIt != out.end() && (pntIt->x < newP.x); pntIt++) {
        lastIt = pntIt;
    }

    if (pntIt == out.end()) {   // insert in last

        cout << "insertP1 : insert last" << endl;
        cout << "  pntIt = (" << pntIt->x << "," << pntIt->y << ") | ";
        cout << "  lastIt = (" << lastIt->x << "," << lastIt->y << ") | ";

        if (out.end()->x == newP.x) {    // same x: take highest y
            cout << "same Pos";
            if (out.end()->y < newP.y) {
                cout << ".... changed";
                out.end()->y = newP.y;
            }
            cout << endl;
        }
        else {
            cout << "NOT same Pos";
            if (lastIt->y < newP.y) {
                cout << ".... ADDED";
                out.push_back(newP);
            }
            cout << endl;
        }

        cout << "  res = (" << out.end()->x << "," << out.end()->y << ") "<< endl;
        res = out.end();
    }

    else if ((lastIt->x != -1) && (pntIt != out.begin()) && (pntIt != out.end())) {  // insert in mid

        cout << "insertP1 : insert mid" << endl;
        cout << "  pntIt = (" << pntIt->x << "," << pntIt->y << ") | ";
        cout << "  lastIt = (" << lastIt->x << "," << lastIt->y << ") | ";

        res = pntIt;
        if (pntIt->x == newP.x) {    // same x: take highest y
            cout << "same Pos";
            if (pntIt->y < newP.y) {
                cout << ".... changed";
                pntIt->y = newP.y;
            }
            cout << endl;
        }
        else {
            cout << "NOT same Pos, ";
            if (lastIt->y < newP.y) {
                out.insert(pntIt,newP);
                res--;
                cout << " lastIt.Y < p1.Y .... inserted";
            }
            cout << endl;
        }

        cout << "  res = (" << res->x << "," << res->y << ") "<< endl;
    }

    else if (lastIt->y == -1) { // insert head
        cout << "insertP1 : insert head " << endl;
        cout << "  pntIt = (" << pntIt->x << "," << pntIt->y << ") | ";
        cout << "  lastIt = (" << lastIt->x << "," << lastIt->y << ")" << endl;

        out.insert(pntIt,newP);

        res = ++lastIt;
    }
    else {
        cout << "ERROR";
        exit(-1);
    }

    return res;

}

void insertP2(list<Point>::iterator p1Pos, Point p2, Point p1) {

    cout << "insertP2: p1Pos = ";
    cout << "(" << p1Pos->x << "," << p1Pos->y << ") | ";
    cout << " out = ";
    for (list<Point>::iterator pntIt = out.begin(); pntIt != out.end(); pntIt++) {
        cout << "(" << pntIt->x << "," << pntIt->y << ") - ";
    }
    cout << endl;

    // insert last
    if (p1Pos == out.end()) {
        cout << " INSERT LAST_1" << endl;
        out.push_back(p2);

        cout << " exit ... out = ";
        for (list<Point>::iterator pntIt = out.begin(); pntIt != out.end(); pntIt++) {
            cout << "(" << pntIt->x << "," << pntIt->y << ") - ";
        }
        cout << endl;

        return;
    }


    list<Point>::iterator res;

    list<Point>::iterator lastIt = LAST_INIT.begin();
    list<Point>::iterator pntIt = p1Pos;

    list<Point>::iterator prevP1Pos = p1Pos;    prevP1Pos--;
    if (prevP1Pos->x == -1) prevP1Pos++;    // adjust, if p1Pos = head



    for (pntIt = p1Pos; pntIt != out.end() && (pntIt->x < p2.x); pntIt++) {

        lastIt = pntIt;

        // browse
        if (pntIt->y < p1.y) {
            pntIt->y = p1.y;
        }
    }

    cout << " prevP1Pos = (" << prevP1Pos->x << "," << prevP1Pos->y << ") | ";
    cout << " pntIt = (" << pntIt->x << "," << pntIt->y << ") | ";
    cout << " lastIt = (" << lastIt->x << "," << lastIt->y << ") " << endl;


    // last
    if (pntIt == out.end()) {

        cout << " INSERT LAST_2" << endl;
        out.push_back(p2);

        cout << " exit ... out = ";
        for (list<Point>::iterator pntIt = out.begin(); pntIt != out.end(); pntIt++) {
            cout << "(" << pntIt->x << "," << pntIt->y << ") - ";
        }
        cout << endl;

        return;
    }


    // no elem
    if (pntIt == p1Pos) {
        cout << " no elem ";

        if (pntIt->x == p2.x) {
            cout << " | p2 same Pos....";
            if (pntIt->y < p1.y) {
                pntIt->y = p1.y;
                cout << "changed";
            }
            cout << endl;

            cout << " exit ... out = ";
            for (list<Point>::iterator pntIt = out.begin(); pntIt != out.end(); pntIt++) {
                cout << "(" << pntIt->x << "," << pntIt->y << ") - ";
            }
            cout << endl;

            return;
        }
        else {
            cout << " | p2 NOT same Pos....";
            if (pntIt->x >  p2.x) {
                out.insert(pntIt,p2);
                cout << "ADD";
            }
            cout << endl;
        }

    }

    if ((pntIt != p1Pos) && (pntIt != out.end())){ // mid

        cout << " mid ";

        if ((pntIt->x != p2.x) && (lastIt->x != p2.x)) {
            cout << " | p2 NOT same Pos....";

            if (lastIt->y == p1.y) {
                cout << " last.Y == p1.y , ADDED P2....";
                out.insert(pntIt,p2);

            } else {    // break
                cout << " last.Y != p1.y , BREAK P2....";
                p2.y = prevP1Pos->y;
                out.insert(pntIt,p2);
            }

            cout << endl << " exit ... out = ";
            for (list<Point>::iterator pntIt = out.begin(); pntIt != out.end(); pntIt++) {
                cout << "(" << pntIt->x << "," << pntIt->y << ") - ";
            }
            cout << endl;

            return;
        }
        else {
            cout << " | p2 SAMEPOS NOT INSERTED...." << endl;
            cout << " exit ... out = ";
            for (list<Point>::iterator pntIt = out.begin(); pntIt != out.end(); pntIt++) {
                cout << "(" << pntIt->x << "," << pntIt->y << ") - ";
            }
            cout << endl;

            return;
        }
    }


    cout << " exit ... out = ";
    for (list<Point>::iterator pntIt = out.begin(); pntIt != out.end(); pntIt++) {
        cout << "(" << pntIt->x << "," << pntIt->y << ") - ";
    }
    cout << endl;
}

void displayOut () {

    list<Point>::iterator lastIt = LAST_INIT.begin();
    int first = 0;

    for (list<Point>::iterator pntIt = out.begin(); pntIt != out.end(); pntIt++) {

        if (first == 0) {
            first++;
            cout << "(" << pntIt->x << ",0)" << endl;
            cout << "(" << pntIt->x << "," << pntIt->y << ")" << endl;
        } else {

            cout << "(" << pntIt->x << "," << lastIt->y << ")" << endl;
            cout << "(" << pntIt->x << "," << pntIt->y << ")" << endl;
        }

        lastIt = pntIt;
    }

}

int main() {

    // init with default value
    init();

    // input
    int nb;
    cin >> nb;
    list<Point>::iterator p1Pos;
    Point p1,p2;

    for (int i = 0; i < nb; i++) {

        cin >> p1.x >> p1.y >> p2.x;    p2.y = 0;

        cout << "p1 = (" << p1.x << "," << p1.y << ")" ;
        cout << "| p2 = (" << p2.x << "," << p2.y << ") | ";

        p1Pos = insertP1(p1);
        insertP2(p1Pos,p2,p1);

    }

    out.pop_front();


    displayOut();

    return 0;
}