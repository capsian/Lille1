all: multif race observation

multif: multif.o
	gcc -Wall -ansi -pedantic -g $^ -o $@

race: race.o
	gcc -Wall -ansi -pedantic -g -static $^ -o $@
	
observation: observation.o
	gcc -Wall -ansi -pedantic -g -static $^ -o $@

%.o: %.c
	gcc -Wall -ansi -pedantic -g -c $^

clean:
	rm -f *.o multif race observation
	
test:
	./test.sh
