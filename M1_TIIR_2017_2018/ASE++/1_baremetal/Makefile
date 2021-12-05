IMAGE=mykernel.iso
BINFILE=mykernel.bin
SRC_DIR=src
INC_DIR=include
BUILD_DIR=build
BIN_DIR=$(BUILD_DIR)/bin
TEST_DIR=tests

##############################

# Toolchain
CC=gcc #x86_64-pc-linux-gnu-gcc
AS=nasm
LD=ld  #x86_64-elf-ld

# Toolchain flags
CFLAGS=-m32 -Wall -Werror -nostdlib -fno-builtin -std=gnu99 -ffreestanding -c -g -Wno-unused-variable -fPIC
LDFLAGS=-melf_i386 -z max-page-size=0x1000
ASFLAGS=-felf

##############################

# Include directories
CFLAGS+=-I$(INC_DIR)

# Sources
CSOURCES=$(wildcard $(SRC_DIR)/*.c)
CSOURCES+=$(wildcard $(SRC_DIR)/*/*.c)
HSOURCES=$(wildcard $(INC_DIR)/*.h)
HSOURCES+=$(wildcard $(INC_DIR)/*/*.h)
ASOURCES=$(sort $(wildcard  $(SRC_DIR)/*.s))
ASOURCES+=$(sort $(wildcard  $(SRC_DIR)/*/*.s))

# Objects
COBJ=$(CSOURCES:.c=.o)
AOBJ=$(ASOURCES:.s=.o)

################################


%.o: %.c $(HSOURCES)
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@


################################

all: $(IMAGE)
	mv mykernel.bin $(BIN_DIR)
	mv mykernel.iso $(BIN_DIR)
	@echo "Done !"

test: all
	sh $(TEST_DIR)/all.sh

$(IMAGE): $(BINFILE)
	cp $(BINFILE) boot/mykernel.bin
	grub-mkrescue -d /usr/lib/grub/i386-pc/ -o $(IMAGE) ./

$(BINFILE): $(AOBJ) $(COBJ)
	$(LD) $(LDFLAGS) -Tlink.ld $^ -o $@
	mv $^ $(BUILD_DIR)

################################

run: all
	qemu-system-x86_64 -boot d -m 2048 -cdrom $(BIN_DIR)/mykernel.iso -serial stdio

################################

.PHONY: $(IMAGE) run

clean:
	rm -f $(BIN_DIR)/* $(BUILD_DIR)/*.o $(AOBJ) $(COBJ) boot/$(BINFILE) $(IMAGE) *.bin
