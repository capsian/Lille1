all:		pol_calcul_final calcul pol_calcul

calcul: 	calculA calculC
			gcc -gstabs -o calcul calculA.o calculC.o
				
calculA: 	calcul.s
		 	gcc -g -c  -o calculA.o calcul.s
				
calculC: 	calcul.c
		 	gcc -g -c  -o calculC.o calcul.c

pol_calcul: 	pol_calculA pol_calculC
		    	gcc -gstabs -o pol_calcul pol_calculA.o pol_calculC.o
				
pol_calculA: 	pol_calcul.s
				gcc -c -g -o pol_calculA.o pol_calcul.s
				
pol_calculC: 	pol_calcul.c
				gcc -c -g -o pol_calculC.o pol_calcul.c

pol_calcul_final: 	pol_calcul_finalA pol_calcul_finalC
		    	gcc -gstabs -o pol_calcul_final pol_calcul_finalA.o pol_calcul_finalC.o
				
pol_calcul_finalA: 	pol_calcul_final.s
				gcc -c -g -o pol_calcul_finalA.o pol_calcul_final.s
				
pol_calcul_finalC: 	pol_calcul_final.c
				gcc -c -g -o pol_calcul_finalC.o pol_calcul_final.c

clean:
				rm pol_calcul_final pol_calcul_finalA.o pol_calcul_finalC.o calcul calculC.o calculA.o pol_calcul pol_calculA.o pol_calculC.o || echo true
