tout: mtail_stupide mtail test

mtail: mtail.o
	gcc -Wall -ansi -pedantic -g $^ -o $@

mtail_stupide: mtail_stupide.o
	gcc -Wall -ansi -pedantic -g $^ -o $@

%.o: %.c
	gcc -Wall -ansi -pedantic -g -c $^

test: test
	./test.sh

clean:
	rm -f *.o mtail mtail_stupide *.txt
