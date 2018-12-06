Bare Metal
=======================

##### Authors
- Jonathan Soleillet <jonathan.soleillet.etu@univ-lille.fr>
- Selim Lakhdar <selim.lakhdar.etu@univ-lille.fr>

##### HOW TO

###### DEPENDENCIES

sudo apt install nasm libc6 libc6-dev libc6-dev-i386 qemu-kvm qemu virt-manager virt-viewer libvirt-bin

###### RUN
	$ mkdir build build/bin
    $ make run

###### TESTS

    $ make tests
    
###### clean

    $ make clean
    $ make realclean
