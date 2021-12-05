CC      = gcc
INCLUDE = -I include/
CFLAGS  = -Wall -Wextra -pedantic -g -D_GNU_SOURCE
LDFLAGS =

BUILD   = build
BIN     = ${BUILD}/bin
SRC     = src
OUTPUT  = output

#######################

%.o: src/*/%.c include/*/%.h
	${CC} ${INCLUDE} ${CFLAGS} -c $< -o ${BUILD}/$@

%.o: src/%.c include/%.h
	${CC} ${INCLUDE} ${CFLAGS} -c $< -o ${BUILD}/$@

%.o: src/%.c
	${CC} ${INCLUDE} ${CFLAGS} -c $< -o ${BUILD}/$@

#######################

all: directory unserializer

unserializer : unserializer.o token.o structs.o environnement.o hashmap.o evaluate.o utils.o
	cd ${BUILD} && ${CC} ${LDFLAGS} -o ../$(BIN)/$@ $^

directory:
	mkdir -p build build/bin output
#######################

test_interprete: realclean directory unserializer
	bash test_interprete.sh

#######################

clean:
	rm -f build/*.o || true

realclean: clean
	rm -rf $(OUTPUT) $(BUILD) || true

.PHONY : all clean realclean
