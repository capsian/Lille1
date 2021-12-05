all: groupe_server groupe_client pwg groupe_server_udp groupe_client_udp

pwg : check_pass.o pwg.o
	gcc -o $@ $^ -lcrypt

groupe_server: check_pass.o groupe_server.o
	gcc -o $@ $^ -lcrypt
	
groupe_server_udp: check_pass.o groupe_server_udp.o
	gcc -o $@ $^ -lcrypt

groupe_client : groupe_client.o
	gcc -o $@ $^
	
groupe_client_udp : groupe_client_udp.o
	gcc -o $@ $^

%.o:%.c
	gcc -c $<

clean:
	rm -f *.o groupe_server groupe_client groupe_client_udp groupe_server_udp
