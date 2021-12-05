
#######  DIRS #######

CC      = gcc -m32
SRC 	= src/
INC 	= include/
BUILD 	= build/
BIN 	= $(BUILD)bin/
TEST	= test/

#######  FLAGS #######

CFLAGS  = -Wextra -pedantic -g
INCLUDE = -I include/
LIBS	= -L lib -lhardware -pthread

#######  RULES #######

all: _build main

#######  COMPLING #######

CSOURCES=$(wildcard $(SRC)*.c)
CSOURCES+=$(wildcard $(SRC)*/*.c)
HSOURCES=$(wildcard $(INC)*.h)
HSOURCES+=$(wildcard $(INC)*/*.h)

COBJ=$(CSOURCES:.c=.o)

%.o: %.c $(HSOURCES)
		$(CC) ${INCLUDE} $(CFLAGS) -c $< -o $@
%.o: %.c
		$(CC) ${INCLUDE} $(CFLAGS) -c $< -o $@

#######  LINKING #######

_build:
	mkdir -p build && mkdir -p build/bin

main : $(COBJ)
	${CC} -g -o $@ $^ $(LIBS)
	mv $(COBJ) $(BUILD)
	mv $@ $(BIN)

#######  TEST #######

_chmod:
	chmod +x $(TEST)*.sh

test: _chmod main
	./$(TEST)/test.sh

#######  CLEAN #######

clean:
	rm -f $(BUILD)*.o

realclean: clean
	rm -f $(BIN)* $(SRC)/*.o

.PHONY: all clean realclean
