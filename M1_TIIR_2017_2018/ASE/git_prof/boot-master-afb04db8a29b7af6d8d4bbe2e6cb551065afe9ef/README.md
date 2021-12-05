Mon premier programme
---------------------

## Le code assembleur #######
Le fichier firstcode.s est de l'assembleur intel destiné à être assemblé avec nasm.
Vous pouvez l'éditer avec : 

	$ vi firstcode.s

## L'assemblage #######
Pour produire un fichier binaire a partir de ce code : 

	$ nasm firstcode.s

Cette commande produit un fichier binaire firstcode.

## Le déassemblage #######
Vous pouvez desassembler le contenu de ce fichier binaire avec la commande :
    
	$objdump -D -b binary -mi386 -Maddr16,data16 firstcode

Chaque octet du fichier est alors "traduit" par le déassembleur en l'instruction intel auquel il 
correspond. Le role du langage assembleur n'et pas d'apporter une abstraction du microprocesseur
mais bien de permettre d'écrire du code microprocesseur, avec des tokens plutot qu'avec leur
valeur numérique. 

## L'écriture du bootsecteur #######

**Attention** lorsque vous écrivez votre programme sur un bootsecteur, vous écrasez les données
pre-existantes. Ne faites cette commande que sur une clef que vous pourrez formater par la suite.

Ce code est un de bootsecteur. Pour pouvoir l'exécuter il faut l'écrire dans le premier bloc 
physique d'un disque qui sera ensuite "booté". Pour l'écrire dans une clef usb par exemple :

	$ sudo dd if=firstcode of=/dev/sd<x> count=1 bs=512 conv=notrunc

Dans cette ligne de commande il convient de remplacer /dev/sd<x> par la lettre qui correspond à
votre clef usb. Pour la connaitre, affichez les /dev/sd* lorsque votre clef n'est pas connectée, 
puis faite de même aprés avoir connecté votre clef...

Notez encore que nous lançons la commande avec les privilège root car elle accède directement 
à un périphérique matériel (la clef usb) à travers un fichier système (/dev/sd<x>). Cela 
constitu un risque important de plantage du support matériel. Les données stockées dans le 
disque pourrait être perdues ou consultées sans que les droits d'accès soient respectés. 

**Nota Bene** Si vous souhaitez récupérer le contenu de votre clef USB aprés cette expérience, 
vous pouvez sauver le bootsecteur avant de l'écraser. Tapez simplement :

	$ sudo dd if=/dev/sd<x> of=oldboot count=1 bs=512 

Le fichier oldboot contiendra les informations que vous allez écraser. Vous n'aurez qu'à remettre
ces informations en place pour "restaurer" votre clef USB :

	$ sudo dd if=oldboot of=/dev/sd<x> count=1 bs=512 conv=notrunc
 

## L'exécution directe #######

Il suffit de rebooter votre machine et de configurer le BIOS pour qu'il démarre sur votre clef USB en
premier. Biensur ce programme ne fonctionnera pas si votre machine ne dispose pas d'un BIOS mais de
EFI (mac par exemple). Il est aussi possible que votre BIOS exige que le programme boot soit "signé"
numériquement par le constructeur. Il sera alors nécessaire de déactiver cette option. 

## L'émulation #######

Un émulateur est un programme qui simule le comportement d'une machine "virtuelle" sur une machine réelle.
Un émulateur tel que qemu vous permettent de démarer le bootsecteur sans redémarer votre machine. 

	$ sudo qemu-system-x86_64 -drive file=/dev/sd<x>,format=raw

Ici nous demandons a qemu de simuler le démarage d'une machine x86 (64 bits) avec comme seul disque
la clef usb "tel qu'elle". Il aurait aussi été possible de donner à qemu un simple fichier vierge
avec notre bootsecteur en tête de fichier. Il n'aurait alors plus été nécessaire de lancer qemu
avec les droits root (sudo). 
 
