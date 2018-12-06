TP ASE++
=====================

Soleillet Jonathan   
Selim Lakhdar  
M1 Informatique - groupe 5  
Le 19/02/2018  
--------------------

# TP 2

Yield on multi-core, using election (a simple round robin).

CORE-0: have to reset timer only !! (and print some info).

    if (nb_ctx < nb_proc)  
        ==> creating new ctx to yield on
    else
        ==> yield normally


## Compile

	make all

## Test

	make test

## Clean

	make clean
	
