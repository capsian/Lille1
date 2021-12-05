CFLAGS = -std=c99

tout: test maccess maccess+ prlimit

maccess: maccess.o
	gcc -std=c99 maccess.c -o maccess

maccess+: maccess+.o
	gcc -std=c99 maccess+.c -o maccess+

prlimit: prlimit.o
	gcc -std=c99 prlimit.c -o prlimit

test: test
	./tests.sh

clean:
	rm -f *.o prlimit maccess maccess+
