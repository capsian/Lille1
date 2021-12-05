all: rmg

rmg : check_pass.o rmg.o
	gcc -o $@ $^ -lcrypt

%.o:%.c
	gcc -c $<

clean:
	rm -f *.o rmg