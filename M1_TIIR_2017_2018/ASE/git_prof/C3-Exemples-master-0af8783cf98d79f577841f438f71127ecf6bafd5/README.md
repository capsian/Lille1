Chapitre 3 - Chargement de code exécutable
==========================================

L'objet de ce chapitre est de vous enseigner :
1. la forme que prend un programme exécutable par le microprocesseur ;
2. les contraintes qu'impose le chargement d'un programme exécutable en mémoire centrale ;
3. les moyens de charger un programme puis de l'exécuter ;
4. les mécanismes de chargement et de liaison dynamique. 

Notion de base
--------------

Exécutez le premier exemple :

	$ vi example.c
	$ gcc example.c
	$ ./a.out

La fonction main retourne 42 au shell.

## Charger et exécuter son premier binaire #######

Essayons de charger le binaire en mémoire et de l'exécuter.

Pour cela, a priori, il suffit de :
1. allouer de la mémoire, et comme par defaut linux
empêche d'exécuter du code dans de la mémoire allouée
il faut lui demander de ne pas le faire ; et d'
2. appeler le fonction d'entrée du fichier binaire, tel qu'elle
est définit par le format binaire `elf` des fichiers exécutables
linux ; c'est le `entrypoint`. 

C'est ce que fait le fichier example2.c :

	$ vi example2.c

Renommez votre binaire exécutable dans un le fichier loaded que 
le programme example2.c veut charger :

	$ mv a.out loaded

Puis compilez :

	$ gcc example2.c

Et exécutez : 

	$ ./a.out

Il "seg fault".... Le "entrypoint" est en 0x400000+epsilon.
Le fichier example2.c n'a pas charger ce programme à 0x400000.

Cette adresse vient du linkscript par défaut de gcc.
Vous pouvez le voir en demandant à gcc de détailler ses
opérations de linkage :. 

	$ gcc examples.c -o loaded -Wl,-verbose | most

Pour décider à quelle adresse mémoire gcc doit placer les fonctions 
qu'il compile et les variables définies par le programme, `gcc`
utilise un `linkscript`.  
Vous pouvez observer dans le `linkscript` par defaut de votre `gcc`
l'addresse utilisée pour le segment de text (code binaire) : 
0x400000.

On peut faire un linkscript avec l'adresse 0, puis le charger
à une adresse `addr` quelquonque et brancher à `addr+entrypoint` :

	$ vi linkscript

Compilez le programme à charger avec ce linkscript :

	$ gcc example.c -o loaded -T linkscript

Relancez le programme de chargement :

	$ ./a.out

Il "seg fault" encore....

Le entrypoint est bien celui que notre chargeur de binaire à
déterminé ?

	$ objdump -f loaded
 
Observez l'adresse de entrypoint déterminé par le programme. Et
cherchez cette adresse dans le fichier binaire (déassemblé) qui 
est chargé : 

	$ objdump -d loaded | most

Observez que la fonction `main` n'est pas à l'adresse indiquée 
par le entrypoint. L'entrypoint exécute `_start`.

Observez aussi qu'il y a de nombreuses fonctions qui sont 
inutiles pour ce qui doit être fait...

Indiquez à `gcc` : 
1. que le point d'entré de votre programme est `main` (option `-e main` passée au linker) ;
2. que vous ne voulez aucune autre fonction que les votres (option `-nostdlib` de gcc)...

	$ gcc example.c -o loaded -T linkscript -Wl,-e,main -nostdlib

Observez qu'il n'y a plus que ce qui est utile :

	$ objdump -f loaded
	$ objdump -d loaded

Exécutez le programme de chargement de binaires exécutables :

	$ ./a.out

Il marche et indique que le programme exécuté retourne 42 !

_(42 est la réponse, Quel était la question déjà ?)._ 

## Répondre au problème de relocation #######

Pourtant, le mécanisme de chargement proposé ne marche pas toujours.

Observez le programme `example2.c` :

	$ vi example2.c

Sauvegardez le premier programme que vous avez reussi à charger :

	$ mv loaded loaded.old

Compilez `example2.c` à la place de `example.c` :

	$ gcc example2.c -o loaded -T linkscript -Wl,-e,main -nostdlib
	$./a.out

"seg fault" (sic !).

	$ objdump -d loaded

Comparez avec l'ancien :

	$ objdump -d loaded.old

La différence est dans l'accès au tableau. Lorsqu'il s'agissait d'une
variable locale le compilateur avait produit un accès indirect indexé
par le registre de pile : 

	mov %edx,-0x30(%rbp,%rax,4) 

Cette instruction assembleur doit être comprise comme suit :
mettre le registre `edx` dans la mémoire à l'adresse 
calculée par `rbp -0x30 + 4*rax`. `rbp` est la base de la pile, `-0x30`
permet de ce placer sur le premier élément du tableau dans la pile
et `+4*eax` permet de se déplacer du nombre d'entier (4 octets)
indiqué par eax depuis le début du tableau (calcul de l'adresse
t[i] utilisé dans le source...)   

dans le nouveau binaire on lit, à la place :

	mov %edx,0x1e0(,%rax,4)

C'est-à-dire : mettre le registre `edx`, dans la mémoire à l'adresse
`0x1e0 + 4*rax`. Ici le compilateur a déterminé que `t` est une variable
globale. En conséquence il lui a attribué un adresse fixe, conformément
au `linkscript` : l'adresse `0x1e0` puisque le `linkscript` demande de 
placer le binaire à l'adresse `0`. Donc quand on lui demande de s'exécuter
il demande une écriture à l'adresse `0x1e0`, ce qui ne plait pas à linux :
"seg fault"...

Dans le fichier binaire on peut voir que le compilateur à utilisé 0x1e0
comme adresse de base pour le tableau `t` :

	$ objdump -t -f loaded

Le programme de chargement de binaire que nous somme en train de mettre 
au point ne charge pas le binaire à l'adresse `0`. Il le charge à une 
adresse allouée dynamiquement, que nous ne pouvons pas connaitre a priori
lorsque nous compilons `example2.c`... Nous ne pouvons donc pas donner
cette adresse à notre `linkscript`. Ce qui aurait été souhaitable 
c'est que le compilateur n'utilise jamais d'instructions qui fasse 
référence à une adresse absolue (comme `0x1e0` dans notre exemple 
précédent). S'il utilisait des adresses "relatives" nous n'aurions pas
de problème. Nous n'avons par exemple pas utilisé l'adresse absolue de `main`
(`0x144`) mais une adresse relative (`elf+0x144`, ligne 25 de `loader.c`).
 
De fait le jeu d'instruction des processeurs intel permet d'exprimer
des adresses absolues, comme `0x1e0` pour le tableau `t`, ou `0x144` pour `main`
par exemple.

Mais il permet aussi d'exprimer des adresses "relatives". C'est le cas 
de `mov %edx, -0x30(%rbp,%rax,4)` par exemple, qui est une adresse relative 
à la base de pile (et indexée par le registre rax*4). 

Les branchements peuvent aussi être, généralement, "relatifs". 
C'est la cas, par exemple, de jmp 172 qui est codé par 0xeb 0x1a. 
0xeb signifie "saut à l'adresse de l'instruction courante + l'octet
suivant" (ici 0x1a soit 26 en décimal). Ce qui nous amène bien en 172
comme l'indique le déassembleur qui à fait le calcul pour nous. 

Finalement, il serait possible d'écrire un code binaire qui n'utilise
que des adressages relatifs plutot que les adressages absolus. Un peu
comme les romans en lipogrammes (tel que "la disparition" qui n'utilise
pas la lettre e).

Le compilateur peut faire cela avec l'option `-fPIC` :

	$ gcc example2.c -o loaded -T linkscript -Wl,-e,main -nostdlib -fPIC

Puis en executant le programme :

	$ ./a.out

Plus de "seg fault". 

Observez que le mode d'adressage qu'a utilisé le compilateur pour atteindre 
la variable globale t :

	$ objdump -d -f loaded

L'instruction mov précédente est remplacée par la séquence :

	lea 0x0(,%rax,4),%rcx
	lea 0x6a(,%rip),%rax
	mov %edx,(%rcx,%rax,1)

Le compilateur à calculé l'index `(4*eax)` qu'il a rangé dans `rcx`. 
Ensuite il a calculer l'adresse de base du tableau comme étant à
`rip+0x6a`, c'est à dire par rapport à l'adresse de l'instruction
qu'il est exécutée, et plus comme une adresse "absolue". 
puis il a écrit `edx` dans la somme des deux précédents...

Le schéma est plus complexe... l'option `-fPIC` complique le
travail du compilateur et elle peut diminuer les performances
brute des programmes (Cependant a moins que vous n'ayez de 
fortes contraintes de performance, cela reste marginal sur 
un processeur intel).

## Compilation et chargement dynamique #######

Observez ce dernier exemple :

	$vi example3.c

Compilez le comme précédement :

	$ gcc example3.c -o loaded -T linkscript -Wl,-e,main -nostdlib -fPIC
  
La compilation échoue. Le compilateur réclame un fonction `puts`
qui n'est pas définit. Cette fonction résulte de l'optimisation par 
gcc de la compilation de la fonction `printf`. Le compilateur
remplace cette dernière par la première lorsqu'il n'y a pas de 
paramêtres supplémentaires pour l'affichage. Ainsi `puts` ne 
"parse" par la chaine à la recherche de "%d" et autres inclusions...

Ce choix du compilateur, de remplacer un appel de fonction par un
autre est discutable. Mais la spécification du c incluant de plus 
en plus explicitement la présente d'une librairie libc, les
compilateurs tel que `gcc` et `clang` optimisent des appels vers cette
dernière. Une option de gcc permet de déactiver cette
optimisation : `-fno-builtin-printf`.

Utilisez cette dernière option :
 
	$ gcc example3.c -o loaded -T linkscript -Wl,-e,main -nostdlib -fPIC -fno-builtin-printf

Ainsi gcc vous indique que la fonction printf n'est pas définie. 
Cela vient du fait que nous compilons sans la librairie standard (-nostdlib). 

Recompilez sans cette option :

	$ gcc example3.c -o loaded -T linkscript -Wl,-e,main -fPIC -fno-builtin-printf

La compilation aboutie. 

Lancez votre programme avec le programme "loader" :

	$ ./a.out

"seg fault"...

Observez le code déassemblé du binaire que le compilateur à produit :

	$ objdump -d -f loaded | less

Trouvez la fonction main. Observez le callq 380 que objdump présente
comme un appel à printf@plt. 

Observez la fonction printf@plt. Elle commence par :

	jmp *0x502(%rip)

C'est-à-dire "saute" à l'adresse qui est indiquée, dans la mémoire,
à l'adresse `rip+0x502`.

Le compilateur a aménagée une table de fonction appelée :

	_GLOBAL_OFFSET_TABLE

Il suppose qu'à la 18ème entrée de cette table, il trouvera 
l'adresse de la fonction `printf`. Normalement, c'est le 
système d'exploitation qui rempli cette table avant de 
lancer le programme. Nous ne l'avons pas fait, c'est pourquoi
cela échoue. 

Utilisation des libraries dynamiques
------------------------------------

Les librairies dynamiques sont des programmes exécutables 
chargés par le système d'exploitation lorsque le programme
principal les solicites. C'est libraries sont dites 
dynamiques, par rapport aux libraries statiques qui 
sont placées par le compilateur directement dans le même 
fichier binaire que le programme principal. Les 
librairies statiques étaient la règle jusqu'au debut des
années 1990. 

Aujourd'hui l'immense majorité des librairies sont faites pour 
être chargées dynamiquement. L'argument retenu est que 
l'emprunte mémoire des binaires est plus faible sur le
disque car de nombreux programmes dupliqueraient dans 
leur binaire des "copies" des librairies de bases.  

## Interet des libraries dynamiques #######

Compilez simplement l'exemple précédent :

	$ gcc example3.c -o a1.out

Compilez le même exemple en indiquant au compilateur
de placer les librairies nécessaires dans le fichier
binaire pour que le système n'ait pas à les charger
dynamiquement, en ajoutant l'option -static : 

	$ gcc -static example3.c -o a2.out

Puis comparer la taille des deux binaires : 

	$ ls -la a*.out


788K pour un "hello world" statique... 

## Chargement dynamique et librairies dynamiques #######

Produire une librarie dynamique est simple :

	$ vi libhello.c

Pour la compiler, il faut indiquer au compilateur qu'on veut
faire une librairie partagée, et que le code doit donc être 
relogeable... (Certains mécanismes du système d'exploitation
peuvent nous affranchir de cette dernière contrainte). 

	$ gcc -shared -fPIC libhello.c -o libhello.so

Pour l'utiliser, c'est simplement un module comme un autre :

	$ vi dynexample.c

Compilez, il faut indiquer qu'on utilise la librairie hello
qui se trouve dans le répertoire courant : 

	$ gcc -L ./ -lhello dynexample.c

Exécutez le programme :

	$ ./a.out

Il plante, parcequ'il ne trouve pas la librairie à charger :

	$ export LD_LIBRARY_PATH=./
	$ ./a.out

## Chargement dynamique implicite et explicite ####### 

Le chargement dynamique présenté ici est dit implicite.
Par abus de langage, certain parle de chargement statique.
Le programme principal ne "demande" pas à charger la
librairie, il se contente de l'appeler. Il est parfois utile
de pouvoir charger explicitement un fichier qui contient
le code compilé d'une librarie dynamique. Par exemple
vous pouvez souhaiter charger tout les "plug-ins" de
votre programme principal, qui sont en fait des 
libraries dynamiques placées dans un répertoire de 
dédiés aux "plug-ins". 

Observez l'exemple suivant pour un chargement dynamique
explicite :

	$ vi loadso.c
 
Ce programme demande au système de charger "libhello.so".
Ensuite il lui demande de retrouver l'adresse de la fonction
qui à comme nom symbolique "hello". Puis il appelle cette
fonction.

Pour le compiler il faut indiquer à gcc que l'on va utiliser
la librairie de chargement dynamique explicite (qui fournie
les fonctions dlopen, dlsym, dlerror et dlclose (et qui
sera elle chargée dynamiquement implicitement (sic!))).

	$ gcc loadso.c -ldl

Vous pouvez executer le programme produit :

	$ ./a.out

Il affiche le message hello world.

## Chargement dynamique dans d'autres langages ####### 

Java charge les classes compilées (les .class) dynamiquement.
De plus la machine virtuelle java, charge ces classes 
"au besoin". 

Observez les sources java example1.java et example1bis.java :

	$ vi example1.java
	$ vi example1bis.java

Que va afficher ce programme ? 

Du code est exécuté "avant" l'appel à la fonction main. 
La machine virtuelle charge une classe, puis l'initialise
en exécutant ce qui est associé à des éléments de classe. 

	$ javac Example1.java

	$ java Example1

Que valent les variables C1.var et C2.var dans l'exemple
suivant ?

	$ vi C1.java
	$ vi C2.java

Compilez :

	$ javac C1.java

Exécutez :

	$ java C1

...

Observez :

	$ java C2

