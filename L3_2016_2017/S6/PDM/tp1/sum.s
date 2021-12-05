.data
	UnNom:
		.long 43
		.long 54
		.long 23
		.long 76
		.string "hello world"
		.float 3.14
	UnAutre:
		.space 4
.text
.globl _start
_start:
		movl $5, %eax
		movl $0, %ebx
		movl $UnNom, %ecx
	top:
		addl (%ecx), %ebx
		addl $4, %ecx
		decl %eax
		jnz top
	done:
		movl $0, %ebx
		movl $1, %eax
		int $0x80

