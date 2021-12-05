.data 
	tmp : .word  
.text
.global main
main:
	read:
		call mread
	print:
		movq $4, %rax
		movq $1, %rbx
		movq $1, %rdx
		int $0x80
	exit:
		movq 	$0, %rbx
		movq 	$1, %rax
		int  	$0x80

.global mread
.type mread, @function
mread:										# %rdx déja intisialisé
	pushq %rbp
	movq %rsp, %rbp
	movq $3, %rax							# sys_print
	movq $0, %rbx							# stdin
	movq $tmp, %rcx							
	int $0x80								# interuption
	movq %rbp, %rsp
	pop %rbp
	ret
