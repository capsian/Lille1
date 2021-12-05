
#######  DIRS #######

CC          = gcc
SRC 		= src/
INC 		= include/
BUILD 	    = build/
BIN 		= $(BUILD)bin/
TEST	 	= test/

#######  FLAGS #######

CFLAGS      =  -Wextra
INCLUDE     = -I include/
LIBS		= -L lib -lpthread

#######  RULES #######

all: _build server client

#######  COMPLING #######

CSOURCES=$(wildcard $(SRC)*.c)
CSOURCES+=$(wildcard $(SRC)*/*.c)
HSOURCES=$(wildcard $(INC)*.h)
HSOURCES+=$(wildcard $(INC)*/*.h)

SVSOURCE=$(wildcard $(SRC)*server*.c)
SVHEADER=$(wildcard $(SRC)*server*.h)
SVOBJ		=$(SVSOURCE:.c=.o)

CLSOURCE=$(wildcard $(SRC)*client*.c)
CLHEADER=$(wildcard $(SRC)*client*.h)
CLOBJ		=$(CLSOURCE:.c=.o)

COBJ=$(CSOURCES:.c=.o)

%.o: %.c $(HSOURCES)
		$(CC) ${INCLUDE} $(CFLAGS) -c $< -o $@
%.o: %.c
		$(CC) ${INCLUDE} $(CFLAGS) -c $< -o $@

#######  LINKING #######

_build:
	mkdir -p build && mkdir -p build/bin

server : $(SVOBJ)
	${CC} -o $@ $^ $(LIBS)
	mv $(SVOBJ) $(BUILD)
	mv $@ $(BIN)

client : $(CLOBJ)
	${CC} -o $@ $^ $(LIBS)
	mv $(CLOBJ) $(BUILD)
	mv $@ $(BIN)

#######  TEST #######

_chmod:
	chmod +x $(TEST)*.sh

test%: _chmod server client
	bash $(TEST)$@.sh

#######  CLEAN #######

clean:
	rm -f $(BUILD)*.o $(SRC)*.o

realclean: clean
	rm -f $(BIN)* $(TEST)/output/*

.PHONY: all clean realclean
