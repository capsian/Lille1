all: suid

suid : suid.o
	gcc -o $@ $^

%.o:%.c
	gcc -c $<

clean:
	rm -f *.o suid

