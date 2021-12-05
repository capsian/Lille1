.data
	varz:
		a .long 13481754
		b .long 1234715
		rez .long 0
.text
.globl _start
_start:
	bcl:
		movl a, %rax
		movl b, %rbx
		div %rbx
	done:
		movl $0, %ebx
		movl $1, %eax
		int $0x80

