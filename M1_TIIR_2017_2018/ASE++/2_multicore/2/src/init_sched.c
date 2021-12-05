#include <stdio.h>

#include "init_sched.h"
#include "ctx.h"
#include "hardware.h"
#include "core.h"

void procs_etoile(int m) {

    do {
        printf(" * [%d] ", _in(CORE_ID));
        for (long int tick_star = 1 << 15; tick_star > 0; tick_star--);
        printf(" * [%d] ", _in(CORE_ID));
    }
    while (m);
}

void procs_plus(int m) {

    do {
        printf(" + [%d] ", _in(CORE_ID));
        for (long int tick_plus = 1 << 20; tick_plus > 0; tick_plus--);
        printf(" + [%d] ", _in(CORE_ID));
    }
    while (m);
}

void procs_minus(int m) {

    do {
        printf(" - [%d] ", _in(CORE_ID));
        for (long long int tick_minus = 1 << 25; tick_minus > 0; tick_minus--);
        printf(" - [%d] ", _in(CORE_ID));
    }
    while (m);
}

void procs_slash(int m) {

    do {
        printf(" / [%d] ", _in(CORE_ID));
        for (long int tick_slash = 1 << 15; tick_slash > 0; tick_slash--);
        for (long int tick_slash = 1 << 15; tick_slash > 0; tick_slash--);
        printf(" / [%d] ", _in(CORE_ID));
    }
    while (m);
}

void procs_point(int m) {

    do {
        printf(" / [%d] ", _in(CORE_ID));
        for (long int tick_point = 1 << 15; tick_point > 0; tick_point--);
        for (long int tick_point = 1 << 20; tick_point > 0; tick_point--);
        printf(" / [%d] ", _in(CORE_ID));
    }
    while (m);
}

void procs_crash(int m) {

    do {
        printf(" / [%d] ", _in(CORE_ID));
        for (long  int tick_crash = 1 << 20; tick_crash > 0; tick_crash--);
        for (long  int tick_crash = 1 << 20; tick_crash > 0; tick_crash--);
        printf(" / [%d] ", _in(CORE_ID));
    }
    while (m);
}

void init_sched() {
    create_ctx(1 << 16, procs_etoile, 0, "star", 0);
    create_ctx(1 << 16, procs_plus,   0, "plus", 0);
    create_ctx(1 << 16, procs_point,  0, "point", 0);
    create_ctx(1 << 16, procs_slash,  0, "slash", 0);
    create_ctx(1 << 16, procs_minus,  0, "minus", 0);
    create_ctx(1 << 16, procs_crash,  (void*) 1, "crash", 0);
}
