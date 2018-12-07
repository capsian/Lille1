#include "functions/ping_pong.h"
#include "system/context.h"
#include "drivers/screen.h"
#include "setup.h"

struct ctx_s ctx_ping;
struct ctx_s ctx_pong;

void launch_ping_pong() {

    if (VERBOSE) {
        puts("f_ping() with pid = "); put_number(RUNNING_PROCESS); puts(" \n");
        puts("f_pong() with pid = "); put_number(RUNNING_PROCESS + 1); puts(" \n");
    }

    create_ctx(16384, f_ping, 0, "ping", 7);
    create_ctx(16384, f_pong, 0, "pong", 8);
}

void f_ping(void *args)
{
    while(1) {
        puts("A") ;
        //switch_to_ctx(&ctx_pong);
        puts("B") ;
        //switch_to_ctx(&ctx_pong);
        puts("C") ;
      //  switch_to_ctx(&ctx_pong);
    }
}

void f_pong(void *args)
{
    while(1) {
        puts("1") ;
        //switch_to_ctx(&ctx_ping);
        puts("2") ;
        //switch_to_ctx(&ctx_ping);
    }
}