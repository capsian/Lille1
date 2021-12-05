rendu séance 2
===================

Selim Lakhdar


---------------------------------
1/

sudo ifconfig enp2s0 up 192.168.1.2

C ne reçoit pas les messages ICMP envoyés en unicast de A vers B. Il les reçoient après que B ce soit déconnecté. Puis C recoit des requetes de "Who has ..... " pour retrouver la destination.

==> Requetes broadcast pour reconstituer l'adresse physique. ( de B )


2/
@MAC-C = 30:B5:C2:04:FA:F3

le switch change de port aléatoirement entre B et C.
À intervalle régulier la table CAM change ( le port change )

Les deux clients reçoivent les ping de A désormais. (Il n'y a plus de différence entre B et C, les deux reçoivent en meme temps)

3/
A et B se partagent les mêmes ports, celui du SW1. et C et Swi2 partagent le même port pour A et B.

A et B peuvent pinguer A après le changement de port.


II.
1/
Après avoir sécuriser le port, B ne peut plus pinguer A, et C ne peut pas pinguer B.

Le mode sticky permet de sauvgarder les anciennes association et de détecter un changement de port (adresse).

2/
Sécurisation des ports active mais fastidieuse (configurer pour chaque port, et le changer à chaque changement de port)

3/

code

III.
1/ les ping sont retransmis en boucle (spam), car aucun des deux switches ne reconnait l'adresse, et espère la trouver en redirigeant la requetes vers un interface connue

2/ lors de la recherche d'un hote inconnue, la requete parcours le réseau.

3/
Au minimum il faut filtrer les deux ports d'un meme switch (où ils bouclent)

4/
Le sotrm-control peut bloquer un trafic légitime lors de la mise en prod dans un réseau important.




5. Arbre recouvrant
---------------------------

1/
S2 est le pont racine.

2/
Toutes les 2sec

3/
les ports qui émettent : 0/1 0/2 de S2 (pont root) et eth0 de A et B.

les ports qui reçoivent: 0/1, 0/2 de S1 et eth1 de A et B.

4/
Destination: Spanning-tree-(for-bridges)_00 (01:80:c2:00:00:00)_
C'est un MAC MULTICAST
Elles ne sont pas diffusées sur l'ensemble du domaine de diffusion.


5.1. Choix du pont racine
--------------------------------
1/
  spanning-tree vlan 1 priority 4096

2/
Si les priorités sont égales. la racine qui est l'@ MAC la plus petite est choisit, grâce au *bridge id*

3/
Pour créer des routes alternatifs.



7 VLAN
---------------------------------------

1/
A reçoit de B uniquement, C reçoit de D uniquement.
(A et B) et (C et D)

2/
Les VLAN permettent d'isoler les ports du switch qui lui sont associées.

3/
12 bits => 4096 VLAN

4/
Les paquets ne puvent pas être interprétés.

5/
Les deux vlan sont toujours isolés.
non

6/
les trames sont ré envoyées.
Dans une grande structure, meme si un VLAN ne comporte aucun utilisateur, les requetes lui seront quand meme envoyées

7/


