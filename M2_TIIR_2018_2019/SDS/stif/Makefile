# Speed up the build
NPROC_EXISTS := $(shell which nproc)
ifeq ($(NPROC_EXISTS),)
CPUS ?= 1 # probably safer on ARM
else
CPUS := $(shell nproc)
endif
$(info [*] Nb of CPUs: ${CPUS})
MAKEFLAGS += --jobs=$(CPUS)

CFLAGS = -Wall -Werror -Wextra -g -I./include
LDFLAGS = -lSDL2

CC = gcc
CC_afl = afl-gcc

all: spcheck fuzzing test

obj/%.o: src/%.c include/%.h
	@mkdir -p obj
	@echo "[*] Building $@"
	${CC} -o $@ -c $< ${CFLAGS}

obj/%.o: src/%.c
	@mkdir -p obj
	@echo "[*] Building $@"
	${CC} -o $@ -c $< ${CFLAGS}

spcheck: obj/main.o obj/stif.o
	mkdir -p bin
	${CC} -o bin/$@ $^ ${LDFLAGS}

fuzzing: src/main.c src/stif.c include/stif.h
	mkdir -p bin obj out in
	cp images/troll.stif images/troll-grayscale.stif in
	${CC_afl} -o obj/afl_main.o -c src/main.c ${CFLAGS}
	${CC_afl} -o obj/afl_stif.o -c src/stif.c ${CFLAGS}
	${CC_afl} -o bin/$@ obj/afl_main.o obj/afl_stif.o ${LDFLAGS}
	afl-fuzz -m none -i in -o out ./bin/fuzzing -i @@ -d

valgrind : spcheck
		valgrind --tool=memcheck bin/spcheck -i images/troll.stif -d

clean:
	@echo "[*] Cleaning"
	rm -rf obj bin in out

.PHONY: all clean
