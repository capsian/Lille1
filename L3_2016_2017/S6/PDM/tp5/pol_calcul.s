.data
.text

/**	
* intisialisé %r15 avec &pile	
**/
.global init
.type init, @function
init:
	pushq %rbp
	movq %rsp, %rbp
	movq 8(%rbp), %rax
	movq 16(%rbp), %rbx
	movq 24(%rbp), %rdx
	movq 32(%rbp), %rcx
	movq %rdi, %r15
	movq %rbp, %rsp
	popq %rbp
	ret


/**
* empiler une valeur dans &pile = %r15
**/
.global empiler
.type empiler, @function
empiler:
	pushq %rbp							# sauvegarde pointeur base
	movq %rsp, %rbp					# rsp = rbp
  #movq 24(%rbp), %rax		# recup val (ne marche pas toujours)
	movq %rdi, %rax					#	recup val (OK)
	movq %rsp, %r14					# sauv &sommet_fonction_empiler
	movq %r15, %rsp					# %rsp = &pile
	push %rax								# ENNFIIINNNN
	movq %rsp, %r15					# sauv nouvelle &pile
  movq %r14, %rsp					# restaurer &sommet_fonction_empiler
	movq %rbp, %rsp     		# restauration pointeur base
	popq %rbp
	ret
	
/**
* depiler valeur depuis &pile = %r15
**/
.global depiler
.type depiler, @function
depiler:
	pushq %rbp  			      # sauvegarde pointeur base
	movq %rsp, %rbp					# rsp = rbp
	movq %rsp, %r14					
	movq %r15, %rsp
	pop %rax
	movq %rsp, %r15
	movq %r14, %rsp
	movq %rbp, %rsp         # restauration pointeur base
	popq %rbp
	ret

.global addition
.type addition, @function
addition:
	push %rbp           /* sauvegarde pointeur base */
	movq %rsp, %rbp
	push %rbx           /* sauvegarde des registres */
	movq 24(%rbp), %rbx  /* on prépare les opérandes */
	movq 32(%rbp), %rax
	addq %rbx, %rax     /* on fait l'addition */
	pop %rbx            /* on restaure les registres */
	movq %rbp, %rsp     /* restauration pointeur base */
	pop %rbp
	ret

.global substract
.type substract, @function
substract:
	push %rbp
	movq %rsp, %rbp
	push %rbx
	movq 24(%rbp), %rbx
	movq 32(%rbp), %rax
	subq %rbx, %rax
	pop %rbx
	movq %rbp, %rsp
	pop %rbp
	ret

.global times
.type times, @function
times:
	push %rbp
	movq %rsp, %rbp
	push %rbx
	movq 24(%rbp), %rbx
	movq 32(%rbp), %rax
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
	movq 24(%rbp), %rbx
	movq 32(%rbp), %rax
	idiv %rbx
	pop %rbx
	movq %rbp, %rsp
	pop %rbp
	ret

