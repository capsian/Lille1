mread	:	mread.o 
		gcc -gstabs -o mread mread.o 

mread.o	:	mread.s       	
		gcc -c -o mread.o mread.s

clean	:
		rm *.o mread || echo True 
	
