#include <stdio.h>
#include <execinfo.h>

long int *local_stack;

void dump_stack() {

    long int anchor = 0xfacade;
    long int* anchor_ptr = &anchor;

    printf("dump_stack() enter ...\n &anchor = %p | &anchor_ptr = %p\n",&anchor,&anchor_ptr);

    while (anchor_ptr <= local_stack) {

		printf(" *%p = %lx\n",anchor_ptr,*anchor_ptr);

        anchor_ptr++;
    }
    printf("dump_stack() exit ...\n");
}

void rec(int d){

    long int rec_local= 0xcafebabe;
    printf("rec() enter ...\n d = %d | &d = %p | &rec_local = %p\n",d,&d,&rec_local);

    if (d>10) {
		dump_stack();
    } else {
		rec(d+1);
	}
    printf("rec() exit ...\n");
}

int main() {

    long int local = 0xdeadbeef;
    local_stack = &local;

    printf("main() enter ... | &local_stack = %p (static) | &local = %p\n&main = %p | &rec = %p | &dump_stack = %p\n",&local_stack,&local,&main,&rec,&dump_stack);

    rec(0);

    printf("main() exit ...\n");
    return 0;
}
