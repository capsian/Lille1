try.o: try.c try.h
	gcc -c try.c

try_mul.o: try_mul.c
	gcc -c try_mul.c

display_stack: display_stack.c
	gcc display_stack.c -o display_stack

try_mul: try_mul.o try.o
	gcc -o $@ try_mul.o try.o

clean:
	rm display_stack try_mul *.o 
