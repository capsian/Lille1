CC      = gcc
CFLAGS  = -Wall -g -std=c99

LDFLAGS  = -g


all: ex ds

%.o: %.c %.h
	${CC} ${CFLAGS} -c $<
	
ex: ex.o graphe.o
	${CC} ${LDFLAGS} -o $@ $^

ds: ds.o graphe.o
	${CC} ${LDFLAGS} -o $@ $^
	
clean :
	rm *.o || true

realclean : clean
	rm ex ds || true
	
.PHONY: all clean realclean
