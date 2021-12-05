.data
	N:
		.byte 3
.bss
	BUFF:
		.space 10
.text
.globl _start
_start:
	mov $3 ,%eax
	mov $0 ,%ebx
	mov $BUFF, %ecx
	mov $3, %edx
	int $0x80
	
	addl $2, BUFF
	
	mov %eax, %edx
	mov $4, %eax
	mov $1, %ebx
	mov $BUFF, %ecx
	int $0x80
	
	addl $1, BUFF
	mov %eax, %edx
	mov $4, %eax
	mov $1, %ebx
	mov $BUFF, %ecx
	int $0x80
	
	mov $1, %eax
	mov $0, %ebx
	int $0x80
