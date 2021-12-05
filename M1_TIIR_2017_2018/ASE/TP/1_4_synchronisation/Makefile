ROOTDIR=.

CC	= gcc-5
CFLAGS	= -m32 -Wall -Wextra -pedantic
CFLAGS  += -g
INCS    = -I$(ROOTDIR)/include
LIBS    = -L$(ROOTDIR)/lib -lhardware

SRC      = ./src
INCLUDE  = ./include
BUILD    = ./build
BIN      = $(BUILD)/bin
TESTS    = ./tests

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

philosophes:philosophes.o yield.o tmr.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/philosophes $(BIN)

prod_cons: prod_cons.o semaphore.o yield.o tmr.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/prod_cons $(BIN)

<<<<<<< HEAD

# ===========================
# TESTS
# ===========================

test_philo: philosophes _chmod
	cd $(TESTS) && ./drive.o.sh


# ===========================

_chmod:
	chmod +x tests/*.sh

# ===========================
=======
semaphore.o: semaphore.c include/semaphore.h include/yield.h
	$(CC) $(CFLAGS) $(INCS) -c src/semaphore.c

philosophes.o: philosophes.c include/semaphore.h
		$(CC) $(CFLAGS) $(INCS) -c src/philosophes.c

prod_cons.o: prod_cons.c include/prod_cons.h include/semaphore.h
	$(CC) $(CFLAGS) $(INCS) -c src/prod_cons.c

tmr.o :tmr.c include/hardware.h include/tmr.h
	$(CC) $(CFLAGS) $(INCS) -c src/tmr.c

yield.o: yield.c include/yield.h include/tmr.h
	$(CC) $(CFLAGS) $(INCS) -c src/yield.c
>>>>>>> a7fe644c69975621ef625a3b07ff287676b5dfb4

clean:
	$(RM) *.o

realclean: clean
	$(RM) philosophes prod_cons

.PHONY: clean realclean depend
