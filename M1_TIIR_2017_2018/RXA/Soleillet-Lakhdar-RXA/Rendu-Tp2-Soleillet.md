Le 22/01/2018  
TP2  
Soleillet Jonathan
---------------

# 1. Commutation

1) Lorsque A envoie des ping vers B, le client C ne reçois pas les trames ICMP.
Mais lorque l'on déconnecte le client B il disparait de la table d'acheminement, le commutateur envoie des requêtes en broadcast ICMP pour trouvé le client B.  
Ici le client C reçois les trames ICMP de A vers B et essaie de trouver le client B.

2) En consultant régulièrement la table CAM du switch, on remarque que le port associé à l'adresse physique de B change. Une fois on a le port où le client B est connecté, une autre fois on le port où le client C est connecté.  

Avec l'ajout des deux ports en static avec l'adresse mac de B, on peut désormais ping B et C en même temps (L'adresse est associé avec les deux ports).  
Si l'on ping B ou C, les deux reçoivent les requêtes.


```
mac address-table static 30b5.c205.0d80 vlan 1 interface Gi1/0/6  
```  

```
mac address-table static 30b5.c205.0d80 vlan 1 interface Gi1/0/10  
```  

3) Les adresses mac du client A et du client B ainsi que celle du 1er switch sont associés au même port sur le 2e switch.




# 2. Sécurisation des ports

1)   
```
configure terminal  
interface Gi1/0/1
switchport mode access
switchport port-security
switchport port-security maximum 1
switchport port-security mac-address sticky
```

Les clients B et C arrivent à ping A.
En mode no sticky :
On peut ping A qui est sur un autre port.
On peut aussi ping B lorsqu'il est connecté au port sécurisé.

En mode sticky :  
Quand B se connecte sur le port sécurisé il obtient une erreur (psecure violation) et ne peut donc recevoir aucune trame.


2)La configuration peut prendre beaucoup de temps si l'on dois ajouter chaque poste sur un port mais dans le cas où quelqu'un voudrait copier notre adresse physique il serait immédiatement détecter et rejeter du réseau.  

3)
```
configure terminal  
interface range Gi1/0/1-24
switchport mode access
switchport port-security
switchport port-security maximum 1
switchport port-security mac-address sticky
```

# 3. Boucle de communication  

1) On remarque beaucoup de trame ICMP dupliqué en ayant lancé qu'une seule requête ICMP
On a un phénomène de boucle, il cherche a joindre les hôtes sur tous le réseau.

2) Lorsque l'hôte de destination est inconnu, le mécanisme pour le trouver tournera en boucle.

3) On a capturé 325887 paquets en 21 secondes.
Il faut filtrer les deux interfaces du 1er switch qui sont connecter sur le 2e switch.

4) En production on peut avoir besoin d'envoyer beaucoup de paquets ou requête qui pourrait être malheureusement détecter par le storm control et donc bloquer.


```
configure terminal
interface Gi1/0/1
storm-control broadcast level 15
end
```

# 4. Bridge linux

```
sudo ifconfig enp1s0 up 0.0.0.0
sudo ifconfig enp3s0 up 0.0.0.0
sudo brctl addbr A
sudo brctl addif A enp1s0
sudo brctl addif A enp3s0
sudo ifconfig A up 192.168.1.1  
```
# 5. Arbre recouvrant

1) Le pont désigné comme "racine" de l'arbre est le switch S2.  

2) La fréquence de transmission des messages STP est de 2 secondes.  

3) Les ports qui émettent sont:
  - le port eth0 des ponts A et B.
  - le port 1 et 2  de S2.  

Les ports qui reçoivent sont :
  - le port eth1 des ponts A et B.
  - le port 1 et de 2 de S1.

4) Address: Spanning-tree-(for-bridges)00 (01:80:c2:00:00:00)  
C'est une adresse MAC multicast.  
Ces trames ne sont pas diffusés sur l'ensemble du domaine de diffusion ethernet.  

# 5.1 Choix du pont racine  

1 )
```
configure terminal
spanning-tree vlan 1 priority 4096
end
```
Le pont élu racine sera le pont avec la priorité la plus basse.  

2) Le pont root sera choisis en fonction de l'adresse MAC la plus petite.
(Bridge-id le plus petit, il est composé de la priorité (2 octets poids forts) et de l'adresse MAC (6 octets restants)).  

3) On met la priorité du pont 2 à 8192 et celle du pont 1 à 4096.  
On désire choisir le pont root afin de pouvoir être sur de ne pas le laisser être choisis au hassard et ainsi d'avoir un pont avec la plus petite puissance.
On préfère mettre en root le noeud le plus gros du réseau.

# 5.2 Choix des ports racines

Root past cost

1) Election du pont Root
2) Choix des ports Root
3) Choix de ports désignés

Les ports non désignés sont mis en blocking.

Etats des ports :
 Blocking
 Listening
 Learning
 Forwardind



# 7-VLAN

1)
Pour le VLAN 2 :  
```
configure terminal
vlan 2
name atelier
ex
interface range Gi1/0/1-2
switchport mode access
switchport access vlan 2
```

Pour le VLAN 3 :

```
configure terminal
vlan 3
name direction
ex
interface range Gi1/0/3-4
switchport mode access
switchport access vlan 3
```

Seul A et B reçoivent le ping émis en diffusion par A (Vlan 2).  
Seul B et C reçoivent le ping émis en diffusion par C (Vlan 3).  

2) Permettre d'isoler les ports associer à un VLAN de sorte qu'un VLAN ne puisse pas directement communiquer avec un autre matériel sur un autre VLAN sur le même réseau.

3)
S1 et S2 :   
Pour le VLAN 2 :   
```
configure terminal
vlan 2
name atelier
ex
interface Gi1/0/1
switchport mode access
switchport access vlan 2
interface Gi1/0/3
switchport mode access
switchport access vlan 2
```

Pour le VLAN 3 :  

```
configure terminal
vlan 3
name direction
ex
interface Gi1/0/2
switchport mode access
switchport access vlan 3
interface  Gi1/0/4
switchport mode access
switchport access vlan 3
```

# 8-Trunk

1)
```
configure terminal
interface Gi1/0/3
switchport nonegotiate
switchport mode trunk
switchport trunk allowed vlan 2-3
switchport trunk allowed vlan add 2
switchport trunk allowed vlan add 3

```

Pour le switch utilisant ISL :

2) On a une encapsulation d'un protocol 802.1Q en plus, qui contient l'ID du vlan de destination.  

3) La taille du champ est de 12 bit : on peut don avoir 4095 Vlans.  

4)
```
switchport trunk encapsulation dot1Q
```  
Si les deux protocles sont différents des deux côté, on ne peut pas utiliser le trunk.  

5)
```
switchport trunk native vlan 2
```

Les vlan 2 et 3 sont toujours isolés.  
Non un seul Vlan natif par trunk.
On remarque que l'encapsulation 802.1Q n'a plus lieu pour les trames du vlan 2.  

6) La trame est tout de même transmisse sur le trunk.  
Celà peut poser des problèmes sur les grands réseaux, envoyé beaucoup de trame pour un vlan sans destinataire génère du trafic inutile.  

7)    

# 9-Surveillance des ports

```
configure terminal
monitor session 1 source interface Gi1/0/3
monitor session 1 destination interface Gi1/0/4 encapsulation dot1q
```

# 10-VTP

1)
```
configure terminal
vtp domain TOTO
vtp mode server
```
Le trunk continue de transmettre les trames envoyés par le VLAN 3.  
Afin que ce qui appartiennent à ce VLAN sur les différents switch puissent continuer de communiquer.

Les paquets VTP sont transmis sur le trunk.
On y retrouve le nom du domaine VTP ainsi que les VLAN que les clients doivent avoir.   
```
VLAN Trunking Protocol
    Version: 0x02
    Code: Subset Advertisement (0x02)
    Sequence Number: 1
    Management Domain Length: 4
    Management Domain: TOTO
    Configuration Revision Number: 8
    VLAN Information
        VLAN Information Length: 20
        Status: 0x00
        VLAN Type: Ethernet (0x01)
        VLAN Name Length: 7
        ISL VLAN ID: 0x0001
        MTU Size: 1500
        802.10 Index: 0x000186a1
        VLAN Name: default
    VLAN Information
        VLAN Information Length: 20
        Status: 0x00
        VLAN Type: Ethernet (0x01)
        VLAN Name Length: 7
        ISL VLAN ID: 0x0002
        MTU Size: 1500
        802.10 Index: 0x000186a2
        VLAN Name: atelier
    VLAN Information
        VLAN Information Length: 20
        Status: 0x00
        VLAN Type: Ethernet (0x01)
        VLAN Name Length: 6
        ISL VLAN ID: 0x0003
        MTU Size: 1500
        802.10 Index: 0x000186a3
        VLAN Name: access
```

S2 (client) ne peut créer de VLAN car seul le serveur VTP peut en créer.  

2) Un switch peut passer en mode serveur et forcer l'ajout de VLAN.Il peut ajouter des VLAN sur les clients et les serveurs du VTP.  

3) Si on a le protocle VTP sur un switch d'une autre marque rien ne nous permet de dire qu'ils seront capable de communiquer avec VTP.  


# 11-Routage inter-vlan

Sur le routeur :  
```
configure terminal
interface Gi0/1
no shutdown
end
configure terminal
interface Gi0/1.2
encapsulation dot1Q 2
ip address 192.168.10.254
end
interface Gi0/1.3
encapsulation dot1Q 3
ip address 192.168.11.254
end
configure terminal
ip routing
end
```
Sur le switch :  
```
configure terminal
interface Gi1/0/5
switchport mode trunk
switchport trunk allowed vlan 2-3
switchport trunk allowed vlan add 2
switchport trunk allowed vlan add 3
```
Sur les clients du VLAN 2 :  

```
sudo route add -net 192.168.11.0 netmask 255.255.255.0 gw 192.168.10.254
```


Sur les clients du VLAN 3 :  

```
sudo route add -net 192.168.10.0 netmask 255.255.255.0 gw 192.168.11.254
```

Les trames 802.1Q peuvent passer « à travers » les routeurs (d'un réseau à un autre).  

# 12-Trunk et serveur

1)
```
vconfig add enp2s0 2
vconfig add enp2s0 3
```

3)
```
switchport trunk allowed vlan 2-3
```

4)
Oui elles sont reçus   
L'ajout du VLAN n'est pas prise en compte sur S2.  
Lorsque l'on ajout un VLAN sur S2, le vlan n'est pas ajouter.  
flash:vlan.dat  
Dans la running config

# 13 Agrégation des liens

1)
```
Interface range Gi1/0/3-5
channel-group 1 mode on
```
