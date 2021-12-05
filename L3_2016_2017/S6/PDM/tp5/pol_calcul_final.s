.data
.text

.global empiler
.type empiler, @function
empiler:
	pushq (%rdi)
	addq $8, %rsp
	ret
	
.global depiler
.type depiler, @function
depiler:
	subq $8, %rsp
	popq %rax
	ret

.global addition
.type addition, @function
addition:
	push %rbp			# sauv pile
	movq %rsp, %rbp
	addq %rdi, %rsi		# rsi = %rdi (a) + %rsi (b)
	movq %rsi, %rax		# val de retour
	movq %rbp, %rsp
	pop %rbp
	ret

.global substract
.type substract, @function
substract:
	push %rbp
	movq %rsp, %rbp
	subq %rsi, %rdi		# rdi = %rsi (a) - %rdi (b)
	movq %rdi, %rax		# val de retour
	movq %rbp, %rsp
	pop %rbp
	ret

.global times
.type times, @function
times:
	push %rbp
	movq %rsp, %rbp
	push %rbx
	movq %rdi, %rbx
	movq %rsi, %rax
	imul %rbx
	pop %rbx
	movq %rbp, %rsp
	pop %rbp
	ret

.global divide
.type divide, @function
divide:
	movq $0, %rdx      /* Sinon problème de division */
	push %rbp
	movq %rsp, %rbp
	push %rbx
	movq %rsi, %rbx
	movq %rdi, %rax
	idiv %rbx
	pop %rbx
	movq %rbp, %rsp
	pop %rbp
	ret