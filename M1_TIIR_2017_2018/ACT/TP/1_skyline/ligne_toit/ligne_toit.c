#include <stdlib.h>
#include <stdio.h>

struct building {
    int x1;
    int h;
    int x2;
};
typedef struct building building;

struct buildingL {
    building b;
    struct buildingL* next;

};
typedef struct buildingL buildingL;

struct point {
    int x;
    int y;
};
typedef struct point point;

struct pointL {
    point p;
    struct pointL* next;

};
typedef struct pointL pointL;

buildingL* buildBldngL(building bldng) {

    buildingL* elem = malloc(sizeof(buildingL));

    elem->b.x1 = bldng.x1;
    elem->b.h = bldng.h;
    elem->b.x2 = bldng.x2;
    elem->next = NULL;

    return elem;
}

void displayLine(pointL* out) {

    pointL* tmp = out;

    while (tmp != NULL) {
        printf(" (%d,%d) ",tmp->p.x, tmp->p.y);
        tmp = tmp->next;
    }
    printf("\n");
    return;
}

point constructP1(building bldng) {

    point p;

    p.x = bldng.x1;
    p.y = bldng.h;

    return p;
}

point constructP2(building bldng) {

    point p;

    p.x = bldng.x2;
    p.y = 0;

    return p;
}

pointL* getDfltPointL() {

    pointL* elem = malloc(sizeof(pointL));

    elem->p.x = -1;
    elem->p.y = -1;
    elem->next = NULL;

    return elem;
}

pointL* buildPointL(point pnt) {

    pointL* elem = malloc(sizeof(pointL));

    elem->p.x = pnt.x;
    elem->p.y = pnt.y;
    elem->next = NULL;

    return elem;
}

void insertP2 (point p1, point p2, pointL* out) {

    pointL* current = out;
    pointL* last = NULL;

    while ( (current != NULL) && (current->p.x < p1.x) ) {
        last = current;
        current = current->next;
    }

    //current = last;

    while ( (current != NULL) && (current->p.x < p2.x) ) {

        if (current->p.y < p1.y) {
            printf(" insertP2: browse : i change (%d,%d) to ",current->p.x, current->p.y);
            current->p.y = p1.y;
            printf(" (%d,%d)\n",current->p.x, current->p.y);
        }

        last = current;
        current = current->next;
    }

    // insert in head
    if ((last == NULL) && (current != NULL)){

        printf(" insert in head P2, TODO\n");
        return;
    }
        // insert in midd
    else if ( (last != NULL) && (current != NULL) ) {

        printf(" insertP2: insert P2 in midd, last = (%d,%d) | current = (%d,%d) | ", last->p.x, last->p.y, current->p.x, current->p.y);
        /*if (current->p.y == 0) {
            printf(" current = 0, i return\n");
            // current->p.x = p2.x;
            return;
        }*/
        if (last->p.x == p2.x) { // same pos, take highest y
            printf(" same lastPos \n");
            if (last->p.y < p1.y) {
                last->p.y = p1.y;

                return;
            }
        }
        if (current->p.x == p2.x) {
            printf(" same currentPos ");
            if (current->p.y == 0) {
                printf(" -- ");
                current->p.y = p1.y;
            }
            printf("\n");
            return;
        }
        if (last->p.x < p2.x) { //insert break

            printf(" last->p.x < p2.x \n");
            pointL* elem = buildPointL(p2);
            elem->p.y = p1.y;

            last->next = elem;
            elem->next = current;
            return;
        }

        printf(" insert new TODO\n");
        pointL* newElem = buildPointL(p2);
        newElem->p.y = p1.y;
        last->next = newElem;
        newElem->next = current;

        return;
    }
        // insert p2 in last pos
    else if ( (last != NULL) && (current == NULL)) {

        pointL* newElem = buildPointL(p2);

        last->p.y = p1.y;
        last->next = newElem;

        printf(" insertP2: insert P in last = (%d,%d) | current = NULL | new = (%d,%d)\n ",last->p.x, last->p.y, newElem->p.x, newElem->p.y);
        return;
    }
    else {
        printf("SHOULD NEVER HAPPEN, pos p2\n");
        displayLine(out);
        exit(0);
    }

}

pointL* insertP1 (point p1, pointL* out) {

    pointL* current = out;
    pointL* last = NULL;

    // seek p1 pos
    while ( (current != NULL) && (current->p.x < p1.x) ) {

        last = current;
        current = current->next;
    }

    // insert p1 in head
    if ( (last == NULL) && (current != NULL) ) {

        // same pos
        if (current->p.x == p1.x) {
            if (current->p.y < p1.y) {
                current->p.y = p1.y;
            }

            return NULL;
        }
        else {
            pointL* newElem = buildPointL(p1);
            newElem->next = out;

            return newElem;
        }

    }
        // insert p1 in midd
    else if ( (last != NULL) && (current != NULL) ) {

        if (last->p.x == p1.x) { // same pos, take highest y
            if (last->p.y < p1.y) {
                last->p.y = p1.y;

                return NULL;
            }
        }
        if (last->p.y < p1.y) { // look last y, insert new elem if lower

            pointL* newElem = buildPointL(p1);
            last->next = newElem;
            newElem->next = current;

            return NULL;
        }

        return NULL;
    }
        // insert p1 in last pos
    else if ( (last != NULL) && (current == NULL)) {

        pointL* newElem = buildPointL(p1);

        last->next = newElem;

        return NULL;
    }
    else {
        printf("SHOULD NEVER HAPPEN, pos p1\n");
        displayLine(out);
        exit(0);
    }
}

pointL* insertBuilding(pointL* out, point p1, point p2) {

    printf(" insertBuilding() ...\n");

    // first insert
    if ((out->next == NULL) && (out->p.y == -1) && (out->p.x == -1)) {

        printf("  first insert ...\n");
        out->p.x = p1.x;
        out->p.y = p1.y;

        pointL* newElem = buildPointL(p2);
        out->next = newElem;

        return out;
    }

    // return pos of p1 in out
    pointL* head = insertP1(p1,out);

    if (head == NULL) {
        insertP2(p1,p2,out);
    } else {
        out = head;
        insertP2(p1,p2,out);
    }


    return out;
}

void addBuilding(building tmp, buildingL* buildingsL) {

    buildingL* elem = buildingsL;
    buildingL* last = NULL;
    buildingL* newB = buildBldngL(tmp);

    while ((elem != NULL) && ( elem->b.x2 < tmp.x2 ) ) {
        last = elem;
        elem = elem->next;
    }

    // head
    if (last == NULL) {
        newB->next = elem;
        return;
    }
    // midd
    if ((last != NULL) && (elem != NULL)) {
        last->next = newB;
        newB->next = elem;
        return;
    }
    // last
    if ((last != NULL) && (elem == NULL)) {
        last->next = newB;
        return;
    }

    last->next = newB;
    return;
}

void cleanDup(pointL* out) {

    pointL* tmp = out;
    pointL* last = NULL;

    while (tmp != NULL) {

        if (tmp->p.x == -1) {
            last = tmp->next;
            free(tmp);
            tmp = last;
            return;
        }

        if (last != NULL) {
            if (last->p.y == tmp->p.y)  {
                last->next = tmp->next;
                free(tmp);
                tmp = last;
            }
        }

        last = tmp;
        tmp = tmp->next;
    }

    return;
}

void displayOut (pointL* out) {

    pointL* tmp = out;
    pointL* last = NULL;
    int first = 0;

    while (tmp != NULL) {

        if (first == 0) {
            first++;
            printf("(%d,%d)\n(%d,%d)\n",tmp->p.x, 0, tmp->p.x, tmp->p.y);
        } else {

            printf("(%d,%d)\n(%d,%d)\n",tmp->p.x, last->p.y, tmp->p.x, tmp->p.y);
        }

        last = tmp;
        tmp = tmp->next;
    }
}

int main() {

    int n;
    buildingL* buildingsL = NULL;
    pointL* out = NULL;

    // size
    scanf("%d",&n);
    buildingsL = malloc(sizeof(buildingL));
    out = malloc(sizeof(pointL));

    //init out
    out->p.x = -1; out->p.y = -1; out->next = NULL;
    buildingsL->b.x1 = -1; buildingsL->b.h = -1; buildingsL->b.x2 = -1; buildingsL->next = NULL;

    // input
    building tmp;
    for (int i=0; i<n; i++) {
        scanf("%d %d %d", &tmp.x1, &tmp.h, &tmp.x2);
        addBuilding(tmp,buildingsL);
    }

    // build
    buildingL* elem = buildingsL;
    point p1;
    point p2;

    while (elem != NULL) {
        printf("\nloop | ");

        printf("building = (%d,%d,%d) | ",elem->b.x1, elem->b.h, elem->b.x2);

        p1 = constructP1(elem->b);
        p2 = constructP2(elem->b);

        printf("p1 = (%d,%d) , p2 = (%d,%d) || out = ",p1.x, p1.y, p2.x, p2.y);
        displayLine(out);

        out = insertBuilding(out,p1,p2);

        cleanDup(out);
        printf("exit loop ... out = "); displayLine(out);

        elem = elem->next;
    }

    displayOut(out);

    return 0;
}