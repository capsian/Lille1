ROOTDIR=.

CC	     = gcc-5
CFLAGS	 = -Wall -Wextra -ansi -pedantic
CFLAGS  += -g

INCDIR  = ./include

LIBDIR   = ../lib
LIBS     = -L$(LIBDIR) -lhardware

SRC      = ./src
BUILD    = ./build
BIN      = $(BUILD)/bin
TESTS    = ./tests

RM       = rm

###################################################

all: build mkhd dmps frmt dvol mkvol mknfs dfs nbloc dbloc if_cfile if_nfile _chmod

###################################################

build:
	mkdir -p $(BUILD) && mkdir -p $(BIN)

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

mkhd: mkhd.o drive.o vol.o bloc.o mbr.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/mkhd $(BIN)

dmps: dmps.o drive.o vol.o bloc.o mbr.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/dmps $(BIN)

frmt: frmt.o drive.o vol.o bloc.o mbr.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/frmt $(BIN)

## 2

dvol: dvol.o drive.o mbr.o vol.o bloc.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/dvol $(BIN)

mkvol: mkvol.o drive.o mbr.o vol.o bloc.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/mkvol $(BIN)

## 3

mknfs: mknfs.o bloc.o drive.o mbr.o vol.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/mknfs $(BIN)

dfs: dfs.o bloc.o drive.o mbr.o vol.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/dfs $(BIN)

nbloc: nbloc.o bloc.o drive.o mbr.o vol.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/nbloc $(BIN)

dbloc: dbloc.o bloc.o drive.o mbr.o vol.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/dbloc $(BIN)

## ifile

if_nfile: if_nfile.o ifile.o inode.o bloc.o drive.o mbr.o vol.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/if_nfile $(BIN)

if_pfile: if_pfile.o ifile.o inode.o bloc.o drive.o mbr.o vol.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/if_pfile $(BIN)

if_cfile: if_cfile.o ifile.o inode.o bloc.o drive.o mbr.o vol.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/if_cfile $(BIN)

if_dfile: if_dfile.o ifile.o inode.o bloc.o drive.o mbr.o vol.o utils.o
	cd $(BUILD) && $(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	mv $(BUILD)/if_dfile $(BIN)

###################################################

test_drive: mkhd dmps frmt _chmod
	cd $(TESTS) && ./drive.o.sh

test_mbr: dvol mkvol _chmod
	cd $(TESTS) && ./mbr.o.sh

test_bloc: mkhd frmt mkvol dvol mknfs dfs nbloc dbloc _chmod
	cd $(TESTS) && ./bloc.o.sh

test_ifile: mkhd frmt mkvol dvol mknfs dfs if_nfile if_cfile if_pfile if_dfile _chmod
	cd $(TESTS) && ./ifile.o.sh

###################################################

_chmod:
	chmod +x tests/*.sh

###################################################

.PHONY: clean realclean depend

clean:
	$(RM) $(BUILD)/*.o

realclean: clean
	$(RM) $(TESTS)/*.bin
