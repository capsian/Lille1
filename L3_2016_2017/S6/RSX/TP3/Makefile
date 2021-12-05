all: sender receiver

%.o:			%.c
					gcc -Wall -g -c $^

sender: 	sender.o
					gcc -Wall -g $^ -o $@
	
receiver: receiver.o
					gcc -Wall -g $^ -o $@	

clean:		
					rm *.o sender receiver || echo True
