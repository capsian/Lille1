mpile: 	mpileA mpileC
	gcc -gstabs -o mpile mpileA.o mpileC.o
				
mpileA: mpile.s
	gcc -c -g -o mpileA.o mpile.s
				
mpileC: mpile.c
	gcc -c -g -o mpileC.o mpile.c

clean:
	rm mpile mpileA.o mpileC.o || echo true
