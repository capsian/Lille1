===== PJE E =====  

Lakhdar Selim   
Renou Théo

===== Séance 1 =====

Objectif :  
	- Découverte de la mbed et mise en place de petit circuit

Prise en main du mbed NXP LPC1768
utilisation de la plateforme developer mbed afin de produire des codes pour le micro-controlleur
utilisation des classes DigitalIn et DigitalOut pour implémenter un interrupteur et manipuler les leds

découverte des différentes pins(pattes)

utilisation de la fonction read permettant d'obtenir l'état de l'input pin
utilisation de wait afin d'imposer un délai entre les différents signaux

branchement de led et de résistance en série 

code pour l'interupteur:

	#include "mbed.h"
	
	DigitalIn  mypin(p6);
	DigitalOut myled(LED1);
	
	int main()
	{
	
	    // Optional: set mode as PullUp/PullDown/PullNone/OpenDrain
	    mypin.mode(PullNone);
	
	    // press the button and see the console / led change
	    while(1) {
	
	        myled = mypin.read(); // toggle led based on value of button
	    }
	}
La led s'allume lorsqu'il y a du courant et s'éteint sinon.

===== Séance 2 et 3 =====

-- Objectif:
	- Faire clignoter des led à une fréquence donnée, grâce à la librairie Timer fournie par RFLPC.  
	- Allumer LED / Interrupteur  
	
-- Réalisation :  
Courant cette séance nous avons pu;

1- Manipuler la librairie RFLPC afin de pouvoir terminer la réalisation de l'interrupteur, grâce à   
	- rflpc_gpio_set_pin_mode_output();  
	- rflpc_gpio_set_pin_mode_input();  

2- Découverte et manipulation des timers fournis par LPC1768 grâce à la librairie RFLPC.  
   Utilisation de l'interface rflpc_timers.  
    les fonctions; 
    	- rflpc_timer_enable();  
    	- rflpc_timer_set_clock();  
    	- rflpc_timer_set_pre_scale_register();  
    	- rflpc_timer_set_callback();  
    	- rflpc_timer_set_match_value();  
    	- rflpc_timer_set_irq_on_match();  
    	- rflpc_timer_start();  
		- rflpc_timer_reset_irq();  
			
== Code Interrupteur == :


	#include <rflpc17xx/rflpc17xx.h>
	
	
	int main() {
	
	    rflpc_gpio_set_pin_mode_input(RFLPC_PIN_P0_23,RFLPC_PIN_MODE_RESISTOR_PULL_UP);
	    rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_15,0);
	    rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_16,0);
	
	    while (1)
	    {
	      if (rflpc_gpio_get_pin(RFLPC_PIN_P0_23) >= 1) {
	
	        for (j = 0 ; j < 10000000 ; ++j);
	        rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_15,1);		// allumer RFLPC_PIN_P0_15
	        for (j = 0 ; j < 10000000 ; ++j);
	        rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_16,1);		// allumer RFLPC_PIN_P0_15
	      } 
	      else {
	
	        for (j = 0 ; j < 10000000 ; ++j);
	        rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_15,0);		// éteindre RFLPC_PIN_P0_15
	        for (j = 0 ; j < 10000000 ; ++j);
	        rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_16,0);		// éteindre RFLPC_PIN_P0_16
	      }
	    }
	
	
	    return 0;
	}
		
			
== Code TIMER == :

	#include <rflpc17xx/rflpc17xx.h>
	
	#define TIMER_TO_TEST RFLPC_TIMER0
	
	RFLPC_IRQ_HANDLER cb() {
	
	  if (rflpc_timer_test_irq(TIMER_TO_TEST, RFLPC_TIMER_MATCH0)) {
	    rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_23,0);
	    rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_15,0);
	    rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_16,0);
	    rflpc_timer_reset_irq(TIMER_TO_TEST, RFLPC_TIMER_MATCH0);
	  }
	
	  if (rflpc_timer_test_irq(TIMER_TO_TEST, RFLPC_TIMER_MATCH1)) {
	    rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_23,1);
	    rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_15,1);
	    rflpc_gpio_set_pin_mode_output(RFLPC_PIN_P0_16,1);
	    rflpc_timer_reset_irq(TIMER_TO_TEST, RFLPC_TIMER_MATCH1);
	  }
	}
	
	int main() {
	
	    rflpc_led_init();
	
	    rflpc_led_set(RFLPC_LED_3);
	    for (i=0;i<100000;i++);
	
	    rflpc_timer_enable(TIMER_TO_TEST);
	    rflpc_timer_set_clock(TIMER_TO_TEST, RFLPC_CCLK);
	    rflpc_timer_set_pre_scale_register(TIMER_TO_TEST, rflpc_clock_get_system_clock());
	    rflpc_timer_set_callback(TIMER_TO_TEST, cb);
	
	    rflpc_timer_set_match_value(TIMER_TO_TEST, RFLPC_TIMER_MATCH1, 1);
	    rflpc_timer_set_match_value(TIMER_TO_TEST, RFLPC_TIMER_MATCH0, 2);
	    rflpc_timer_set_irq_on_match (TIMER_TO_TEST,RFLPC_TIMER_MATCH1,RFLPC_TIMER_IRQ_ON_MATCH);
	    rflpc_timer_set_irq_on_match (TIMER_TO_TEST,RFLPC_TIMER_MATCH0,RFLPC_TIMER_IRQ_ON_MATCH | RFLPC_TIMER_RESET_ON_MATCH);
	
	    rflpc_timer_start(TIMER_TO_TEST);
	
	
	    while (1)  {}
	
	
	    return 0;
	}

===== Séance 4 =====

Séance 4

Objectif :  
	Allumer LED / Interrupteur  
	RJ45 : cablage + détection branchement/débranchement  
	
Manipulation de la carte Ethernet;  
	cablage :  
		LEDA   = p15  
		LEDB   = p16  
		GND    = GND  
		VCC3.3 = VOUT  
		TPIN+  = RD-  
		TPIN-  = RD+  
		TPOUT+ = TD-  
		TPOUT- = TD+  

== Code detection branchement/débranchement == :

	EthAddr mac_addr;
	
	int main() {
	
	  mac_addr.addr[0] = 2;
	  mac_addr.addr[1] = 3;
	  mac_addr.addr[2] = 4;
	  mac_addr.addr[3] = 5;
	  mac_addr.addr[4] = 6;
	  mac_addr.addr[5] = 7;
	
	  rflpc_led_init();
	  rflpc_eth_init();
	
	  while (1) {
	
	    if (rflpc_eth_link_state()) {
	      rflpc_led_set(RFLPC_LED_1);
	    }
	    else {
	      rflpc_led_clr(RFLPC_LED_1);
	    }
	  }
	
	  return 0;
	}
	
	
===== SMEWS =====

Durant les dernières séances nous avons utilisé le serveur web SMEWS sur la carte MBED.

Pour démarrer le serveur, exécuter les deux scripts :  
	**setup.sh**  
	**install.sh**  
	
**Cartes :**  
	MBED  
	MBED SHIELD  
	MBED BASE  