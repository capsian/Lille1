ROOTDIR=.

CC	     = gcc
CFLAGS	 = -m32 -Wall -Wextra -ansi -pedantic
CFLAGS  += -g

INCDIR  = ./include

LIBDIR   = ../lib
LIBS     = -L$(LIBDIR) -lhardware

SRC      = ./src
BUILD    = ./build
BIN      = $(BUILD)/bin
TESTS    = ./tests

RM       = rm -rf

###################################################

all: static_mmu _chmod

###################################################

%.o: $(SRC)/*/%.c $(INCDIR)/*/%.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(BUILD)

%.o: $(SRC)/*/%.c
	$(CC) $(CFLAGS) -c $<
	mv *.o $(BUILD)

%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $<
	mv *.o $(BUILD)

###################################################

## 1

basic_mmu: basic_mmu.o utils.o mmu.o
	ls && cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/basic_mmu $(BIN)

static_mmu: static_mmu.o utils.o mmu.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/static_mmu $(BIN)

## 2

swap_mmu: mi_kernel.o utils.o mmu.o mmu_handler_1.o swap.o mi_user.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/swap_mmu $(BIN)

## 3

mmu_manager: mmu_manager.o user_process.o matrix.o swap.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/mmu_manager $(BIN)

oracle: oracle.o matrix.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/oracle $(BIN)

###################################################

tests_static: basic_mmu static_mmu _chmod
	cd $(TESTS) && ./static_mmu.sh

tests_swap: swap_mmu _chmod
	cd $(TESTS) && ./swap.sh
	
tests_matmul: mmu_manager oracle _chmod
	cd $(TESTS) && ./matmul.sh

###################################################

_chmod:
	chmod +x tests/*.sh

###################################################

.PHONY: clean realclean depend
clean:
	$(RM) $(BUILD)/*.o

realclean: clean
	$(RM) $(BIN)/* $(TESTS)/*.swap_file $(TESTS)/*.out
