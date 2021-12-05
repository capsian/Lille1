all: pwg

pwg : check_pass.o pwg.o
	gcc -o $@ $^ -lcrypt

%.o:%.c
	gcc -c $<

clean:
	rm -f *.o pwg