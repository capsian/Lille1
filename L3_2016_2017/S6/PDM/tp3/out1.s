.data
	tab:
		.long 0,0,0,0,0
	tmp:
		.space 2
.text
.globl _start
_start:

lecture:

	mov $3 ,%eax
	mov $0 ,%ebx
	mov $tmp, %ecx
	mov $1, %edx
	int $0x80
	mov tmp, %r8
	sub $48, %r8
	add $tab, %r10
	mov %r8, tab
	add $4, %r10b
	cmp $20, %r10
	jne lecture

affichage:
	mov $4, %eax
	mov $1, %ebx
	mov $tab, %ecx
	int $0x80
	
exit:
	mov $1, %eax
	mov $0, %ebx
	int $0x80
