


# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)
        obj-m := src/timer_module.o
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else
	KERNELDIR ?=/home/m1/soleillet/Documents/ASE++/my-kernel/3_noyau_linux/skel/linux-4.15.13/
	BUILDDIR  ?=/home/m1/soleillet/Documents/ASE++/my-kernel/3_noyau_linux/skel/build/kvm32/
 	PWD := $(shell pwd)

all: default kvm realclean

default:
	$(MAKE) -C $(KERNELDIR) O=$(BUILDDIR) M=$(PWD) modules

endif



kvm:
	scp -P 10022 src/timer_module.ko ase@127.0.0.1:

clean:
	rm src/*.o src/*.ko src/*.mod.c

realclean: clean
	rm -rf  modules.order Module.symvers .tmp_versions .cache.mk src/.*.cmd
