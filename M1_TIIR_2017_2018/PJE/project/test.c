/*
#include <rflpc17xx/rflpc17xx.h>
#include "generators.h"
#include "channels.h"

*/
/*
<generator>
  <handlers init="init" doGet="processGet"/>
  <properties interaction="alert" persistence="volatile" channel="comet"/>
</generator>
*//*


static char trigger_input(struct args_t *args) {
	
	server_push(&comet); // Alors on push sur le channel commet en utilisant le doGet (CF XML)
	
	return 1;
}

static char init() {
	
	rflpc_led_init();
	
	rflpc_led_set(RFLPC_LED_1);
	
	set_timer(trigger_input, 1000);
	
	printf("init .... DONE ! \n\r");
	
	return 1;
}

static char processGet(struct args_t *args) {
	
	printf("processGet !\n\r");
	
	out_str("NO ARGS\r\n");
	
	return 1;
}*/
