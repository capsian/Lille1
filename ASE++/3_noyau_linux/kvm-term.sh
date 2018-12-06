#!/bin/bash
KERNEL=${1-/home/m1/soleillet/Documents/ASE++/my-kernel/3_noyau_linux/skel/build/kvm32/arch/x86/boot/bzImage}
#KERNEL=${1-/home/lipari/devel/linux-3.16.3/arch/x86/boot/bzImage}
SMP=${2-2}

kvm -smp $SMP -m 2048 -boot c \
  -hda /local/soleillet/debian32.img \
  -net nic -net user,hostfwd=tcp::10022-:22 \
  -serial stdio \
  -kernel $KERNEL -append "root=/dev/sda1 console=ttyS0 rw" \
  -display none
