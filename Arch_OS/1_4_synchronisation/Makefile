ROOTDIR=/home/enseign/ASE
#ROOTDIR=.

CC	= gcc
CFLAGS	= -m32 -Wall -Wextra -pedantic
CFLAGS  += -g

INCS    = -I$(ROOTDIR)/include
LIBS    = -L$(ROOTDIR)/lib -lhardware

#LIBDIR   = ./lib
#LIBS     = -L$(LIBDIR) -lhardware

SRC      = ./src
INCLUDE  = ./include
BUILD    = ./build
BIN      = $(BUILD)/bin
TESTS    = ./test

# ====================

all: philosophes prod_cons

# ====================

%.o: $(SRC)/%.c $(INCLUDE)/%.h
	$(CC) $(CFLAGS) -c $<
	mv *.o $(BUILD)

%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $<
	mv *.o $(BUILD)

# ====================

philosophes: philosophes.o yield.o tmr.o semaphore.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/philosophes $(BIN)

prod_cons: prod_cons.o semaphore.o yield.o tmr.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/prod_cons $(BIN)

# ===========================
# TESTS
# ===========================

test_philo: philosophes
	./test/philosophes.sh

test_prodcons: prod_cons
	./test/prod_cons.sh

# ===========================

_chmod:
	chmod +x test/*.sh

# ===========================

clean:
	$(RM) $(BUILD)/*.o

realclean: clean
	$(RM) $(BIN)/* *.bin

.PHONY: clean realclean depend
