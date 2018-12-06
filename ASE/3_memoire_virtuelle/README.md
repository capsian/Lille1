### Q1.1

Le programme boucle sur un seg.fault à l'adresse 0

### Q1.2

Rajouter un exit(FAILURE) dans la fonction mmuhandler()

### Q2.1

Le programme seg.fault lors de la deuxième  
    `IRQVECTOR[MMU_IRQ] = mmuhandler;`  
Car nous sommes en mode utilisateur ( _mask(1001))

### Q2.2

VOIR CODE


### TESTS
    make tests_static  
    make tests_swap  
    make tests_matmul  