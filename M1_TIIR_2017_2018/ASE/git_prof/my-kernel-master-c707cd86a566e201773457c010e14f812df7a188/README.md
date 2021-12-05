first kernel
------------

The first kernel project is a skeleton for low level direct programming of x86 hardware. 
It builds a simple bootable .iso file using grub and running your main.c file. 

## files description
 
Here is the initial file structure of the project : 

```
	.
	├── boot		The directory structure used by grub-mkrescue to build a bootable .iso
	│   └── grub		
	│       ├── grub.cfg	The grub configuration file
	│       └── unicode.pf2	The unicode font used by grub
	├── CONTRIBUTORS.md	The contributors list of this skeleton
	├── include		The directory used to store .h file
	    ├── ioport.h	C wrapper to in and out intel assembly instructions 
	    ├── gdt.h		Global Descriptor Table interface providing a default setup
	    ├── idt.h		Interrupt Descriptor Table configuration and interface
	├── LICENSE		The GNU General Public Licence used by this project
	├── link.ld		The link script used by gcc to build the project
	├── Makefile		The makefile building mykernel.iso from the source 
	├── README.md		This file (using markdown)
	└── src			The directory used to store the assembly and C sources
	    ├── 0boot.s		The actual entrypoint called by multiboot
	    ├── idt0.s		Interrupt Descriptor Table assembly routines
	    ├── idt.c		Interrupt Descriptor Table configuration and interface
	    ├── gdt.c		Global Descriptor Table configuration and interface
	    └── main.c		The main.c file where the main() is implemented.
```

## get started

The source of your kernel is splitted in five files : 
1. 0boot.s 
2. main.c
4. gdt.c
5. idt0.s
6. idt.c

0boot.s is the real entry point of your kernel. It just stops hardware interrupt, sets a call-stack and
jumps to the C main with the multiboot structure address as argument of main.

IDT and GDT-related files should be working out of the box, and configure the CPU on boot. You can play
with the IDT configuration to handle various interrupts (an example is given in main()).

main.c is the C code that will run : your kernel ! You can change it in order to print "Hello My World".

	$vi src/main.c   

In order to build you first kernel, just run the Makefile :

	$ make

"make" will assembly the assembly code (using nasm) and compile the C code (using gcc). 

It will use a specific link script "./link.ld" to build the binary image (using ld). 

The binary image (namely mykernel.bin) will be copied in ./grub/ in order to build the .iso file 
(using grub-mkrescue). 

If nothing goes wrong you will get a "mykernel.iso" file in "./" of the project. 
You can burn it to run your software. In this case your code will be run on a bare metal environment. 
This is the goal of the project. Nevertheless, developping software on bare metal environment is boring.
You don't have your usual "operating system facility" to run and test your software. 
Most of the time, a bug will conclude by freezing or rebooting the machine. So we invite you to debug your
kernel on an emulator, namely qemu.

In order to run your .iso file on qemu just try :

	$ make run

qemu will emulate an x86 hardware environment running your iso file. That's it ! 


You could also clean your project using :

	$ make clean


