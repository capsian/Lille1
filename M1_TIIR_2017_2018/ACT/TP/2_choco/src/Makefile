BUILD=../build/
CC=g++

all : naif dynamique dyn_sym dyn_sym127 dyn_sym_minimal_space dyn_sym_minimal_space_try

naif: naif.cpp
	$(CC) naif.cpp -o ../build/naif

dynamique: dynamique.cpp
	$(CC) dynamique.cpp -o $(BUILD)dynamique

dyn_sym: dyn_sym.cpp
	$(CC) dyn_sym.cpp -g -o $(BUILD)dyn_sym

dyn_sym127: dyn_sym127.cpp
	$(CC) dyn_sym127.cpp -o $(BUILD)dyn_sym127

dyn_sym_minimal_space: dyn_sym_minimal_space.cpp
	$(CC) dyn_sym_minimal_space.cpp -g -o $(BUILD)dyn_sym_minimal_space


dyn_sym_minimal_space_try: dyn_sym_minimal_space_try.cpp
	$(CC) dyn_sym_minimal_space_try.cpp -g -o $(BUILD)dyn_sym_minimal_space_try
clean:
		rm $(BUILD)*.o || true

realclean:
	rm $(BUILD)naif $(BUILD)dynamique $(BUILD)dyn_sym $(BUILD)dyn_sym127 $(BUILD)dyn_sym_minimal_space

.PHONY : all clean realclean
