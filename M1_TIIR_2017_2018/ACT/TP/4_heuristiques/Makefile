CC1     = g++
CC2     = gcc
CFLAGS  = -g
SRC     = ./src
BUILD   = ./build
TESTS   = ./tests

##############################

all: _build main _chmod

##############################

%.o: $(SRC)/%.cpp $(SRC)/%.h
	$(CC1) $(CFLAGS) -c $<
	mv *.o $(BUILD)

%.o: $(SRC)/%.cpp
	$(CC1) $(CFLAGS) -c $<
	mv *.o $(BUILD)

##############################

main: main.o input.o first_try.o my_qsort.o stat.o calculate.o fifo.o
	cd $(BUILD) && $(CC1) $(CFLAGS) -o $@ $^

##############################

_build:
	mkdir -p build && cd tests/ && mkdir -p output

_chmod:
	chmod +x $(TESTS)/*

test_main: _build main
	cd $(TESTS) && ./main.sh

test_stat: _build main
	cd $(TESTS) && ./stat.sh

#############################

clean:
	rm $(BUILD)/*.o || true

realclean: clean
	rm $(TESTS)/output/*

.PHONY: all clean realclean
