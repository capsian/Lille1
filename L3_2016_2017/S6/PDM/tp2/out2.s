.data
	Symb:
		.byte 42
.bss
	BUFF:
		.space 10
.text
.globl _start
_start:
	mov $3 ,%eax
	mov $0 ,%ebx
	mov $BUFF, %ecx
	mov $10, %edx
	int $0x80
	
	mov $0, %r10b
	
length:
	movb [BUFF+%r10b], %r8b
	inc %r10b
	sub $48 , %r8b
	movb %r8b, BUFF
	
boucle:
	movl %eax, %edx
	movl $4, %eax
	movl $1, %ebx
	movl $Symb, %ecx
	int $0x80
	movb BUFF, %r8b
	dec %r8b
	movb %r8b, BUFF 
	cmp $0, %r8b
	jne boucle

exit:
	mov $1, %eax
	mov $0, %ebx
	int $0x80	
