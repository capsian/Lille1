	# r15 <=> rsp_main
	# r14 <=> rsp_mstack

/**
* %r14 = %rsp <=> rsp_main
**/
.global init
.type init, @function
init:
	movq %rsp, %r14
	ret

/**
* empiler une valeur dans rsp_mstack <=> %r14
**/
.global empiler
.type empiler, @function
empiler:
	movq %rsp, %r15					# sauv %r15 = %rsp <=> rsp_main
	movq %r14, %rsp
	pushq %rdi
	movq %rsp, %r14
	movq %r15, %rsp 				# rest %rsp = %r15 <=> rsp_main
	ret
	
/**
* depiler valeur depuis rsp_mstack = %r14
**/
.global depiler
.type depiler, @function
depiler:
	movq %rsp, %r15
	movq %r14, %rsp 				# %rsp = rsp_mstack	(old)
	popq %rax
	movq %rsp, %r14					# %r14 = rsp_mstack	(new)
	movq %r15, %rsp
	ret
