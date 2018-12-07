ASE ++ : Linux Kernel Programming
=======================


### Authors
* Selim Lakhdar
* Jonathan Soleillet


### module_0 : kbprob test
    `cd module_0 && make`
    
### module_1 : timer module 
    `cd module_1 && make && make kvm`  

#### KVM
    `insmod timer_module.ko`
    `echo "1234" > /proc/ase_cmd`
    `cat /proc/ase/1234`
    `rmmod timer_module`
    `dmesg`
