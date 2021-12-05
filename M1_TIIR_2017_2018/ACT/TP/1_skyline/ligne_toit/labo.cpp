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

        if (out.end()->x == newP.x) {    // same x: take highest y
            if (out.end()->y < newP.y)
                out.end()->y = newP.y;
        }
        else {
            if (lastIt->y < newP.y)
                out.push_back(newP);
        }

        res = out.end();
    }

    if ((lastIt != LAST_INIT.begin()) && (pntIt != out.begin()) && (pntIt != out.end())) {  // insert in mid

        res = pntIt;
        if (pntIt->x == newP.x) {    // same x: take highest y  (pntIt *=> ?? )
            if (pntIt->y < newP.y)
                pntIt->y = newP.y;
        }
        else {
            if (lastIt->y < newP.y) {
                out.insert(pntIt,newP);
            }
        }
    }

    return res;

}

void insertP2(list<Point>::iterator p1Pos, Point p2, Point p1) {

    list<Point>::iterator res;

    list<Point>::iterator lastIt = LAST_INIT.begin();
    list<Point>::iterator pntIt = p1Pos;

    list<Point>::iterator p1Prev = p1Pos;
    list<Point>::iterator p1Next = p1Pos;

    int lastY;

    p1Prev--;
    p1Next++;

    cout << " insertP2: p2 = (" << p2.x << "," << p2.y << ") || p1Prev = (" << p1Prev->x << "," << p1Prev->y << ") || browse = ";


    if (p1Pos == out.end()) {
        cout << " INNIT " << endl;
        out.push_back(p2);
        return;
    }


    for (pntIt = p1Pos; pntIt != out.end() && (pntIt->x < p2.x); pntIt++) {

        lastY = pntIt->y;
        lastIt = pntIt;

        cout << " (" << pntIt->x << "," << pntIt->y << ") ";
        // browse
        if (pntIt->y < p1.y) {
            pntIt->y = p1.y;
        }


    }

    // no elem
    if (pntIt == p1Pos) {
        cout << endl << " no elem || pnt = ("<< pntIt->x << "," << pntIt->y << ") last = ("<< lastIt->x << "," << lastIt->y << ")";

        p1Prev--;

        if (pntIt->x == p2.x) {
            if (pntIt->y < p1Pos->y) {
                pntIt->y = p1Pos->y;
            }
            return;
        }
        else {
            cout << " ADDED !!" << endl;
            if (pntIt->x >  p2.x)
                out.insert(pntIt,p2);
        }

    }

    if ((pntIt == out.end()) && (lastIt->x != - 1)) { // last
        if (lastIt->y != 0) {
            cout << endl << " last || pnt = ("<< pntIt->x << "," << pntIt->y << ") last = ("<< lastIt->x << "," << lastIt->y << ")" << endl;
            out.push_back(p2);
        }
    }

    if ((pntIt != p1Pos) && (pntIt != out.end())){ // mid
        cout << endl << " mid || pnt = ("<< pntIt->x << "," << pntIt->y << ") p1Prev = ("<< p1Prev->x << "," << p1Prev->y << ") last = ("<< lastIt->x << "," << lastIt->y << ") | lastY = " << lastY << endl;

        if (pntIt->x == p2.x) {
            if (pntIt->y < p1Pos->y) {
                pntIt->y = p1Pos->y;
            }
            return;
        }
        else {
            cout << " ADDED !!" << endl;
            if (lastY >  p2.y) {
                p2.y = lastY;
                out.insert(pntIt,p2);
            }

        }
    }
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

        p1Pos = insertP1(p1);
        cout << "loop " << i << " p1pos = (" << p1Pos->x << "," << p1Pos->y << ") || out = ";
        for (list<Point>::iterator pntIt = out.begin(); pntIt != out.end(); pntIt++) {
            cout << "(" << pntIt->x << "," << pntIt->y << ") - ";
        }
        cout << endl;
        insertP2(p1Pos,p2,p1);
        cout << "loop " << i << " exit ... || out = ";
        for (list<Point>::iterator pntIt = out.begin(); pntIt != out.end(); pntIt++) {
            cout << "(" << pntIt->x << "," << pntIt->y << ") - ";
        }
        cout << endl<< endl;
    }

    out.pop_front();

    cout << endl << " *********** " << endl;
    for (list<Point>::iterator pntIt = out.begin(); pntIt != out.end(); pntIt++) {
        cout << "(" << pntIt->x << "," << pntIt->y << ") - ";
    }
    cout << endl << " ********** " << endl;

    cout << endl << "#############" << endl;
    displayOut();
    cout << endl << "#############" << endl;

    return 0;
}