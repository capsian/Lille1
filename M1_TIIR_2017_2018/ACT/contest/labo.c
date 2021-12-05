//
// Created by worker on 23/09/17.
//

#include <stdio.h>
#include <stdlib.h>

struct point {
    int x;
    int y;
};
typedef struct point point;

struct list {
    point p;
    struct list* next;
};
typedef struct list list;

list* getDflt() {

    list* elem = malloc(sizeof(list));

    elem->p.x = -1;
    elem->p.y = -1;
    elem->next = NULL;

    return elem;
}

list* addElem(list* l) {

    list* tmp = l;
    list* elem = getDflt();
    printf("addElem: tmp->next = %p, elem->next = %p\n",tmp->next, elem->next);

    while (tmp->next != NULL) {
        printf(" .");
        tmp = tmp->next;
    }
    tmp->next = elem;
    printf("\n");
    return l;
}

void displayLine(list* out) {

    list* tmp = out;
    while (tmp->next != NULL) {
        printf(" (%d,%d) | ",tmp->p.x, tmp->p.y);
        tmp = tmp->next;
    }
    printf("\n");
    return;
}

int main() {

    list* l = malloc(sizeof(list));
    l->p.x = 0; l->p.y = 0; l->next = NULL;

    displayLine(l);
    l = addElem(l);
    displayLine(l);
    l = addElem(l);
    displayLine(l);
    l = addElem(l);
    displayLine(l);

    return 0;
}
