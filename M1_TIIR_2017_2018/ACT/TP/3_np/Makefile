CC1     = g++ -std=c++11
CC2     = gcc
CFLAGS  = -g
SRC     = ./src
GRAPHE  = $(SRC)/graphe
BUILD   = ./build
TESTS   = ./tests

##############################

all: main graphToVisu _chmod

##############################

%.o: $(SRC)/%.cpp $(SRC)/%.h
	$(CC1) $(CFLAGS) -c $<
	mv *.o $(BUILD)

%.o: $(SRC)/%.cpp
	$(CC1) $(CFLAGS) -c $<
	mv *.o $(BUILD)

%.o: $(GRAPHE)/%.c $(GRAPHE)/%.h
	$(CC2) $(CFLAGS) -c $<
	mv *.o $(BUILD)

##############################

main: main.o np.o matrix_quicksort.o british_museum.o tree.o  utils.o graphe.o
	cd $(BUILD) && $(CC1) $(CFLAGS) -o $@ $^

graphToVisu : graphToVisu.o graphe.o
	cd $(BUILD) && gcc $(CFLAGS) -o $@ $^

##############################

_chmod:
	chmod +x $(TESTS)/*

test:
	cd $(TESTS) && ./test.sh

#############################

clean:
	rm $(BUILD)/*.o || true

realclean:
	rm $(BUILD)/* $(TESTS)/*.ps $(TESTS)/*.dot $(TESTS)/*.grp

.PHONY: all clean realclean
