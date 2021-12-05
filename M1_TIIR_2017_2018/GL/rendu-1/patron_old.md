Sujet 1 - Petites annonces
===============

- Groupe _5_ (Enseignant _Giuseppe Lipari_)
### Équipe 3:
 * Dambrine Valentin
 * Deregnaucourt Benjamin
 * Lakhdar Selim
 * Oswalt Rémi
 * Soleillet Jonathan

### Versions
- Version: 1.0 - 15/09/2017
- Version: 2.0 - 04/10/2017

# I. Introduction generale #

- Pourquoi cette application ?

  Cette application est née du besoin d'avoir une plate-forme de revente entre particuliers de façon sécurisée et simple, en cherchant autour de chez soi en priorité.

- Quels sont ses caractéristiques principales ?

  L'application permet la création, la consultation et la gestion de petites annonces entre particuliers en proposant un système de réputation sur les profils.

- Quels sont les objectifs ?

  Les objectifs sont donc la mise à disposition d'outils pour mettre en avant les produits que les utilisateurs veulent vendre.

# II. Scénarios concrets #

## 1. Acheteur
-------------

Eudes, un collectionneur de jeux rétro utilise régulièrement MaBrocrante pour trouver des nouveaux produits dans le but d'étoffer sa collection, profitant de la
naïveté des vendeurs du site pour obtenir des raretés à moindre coût.  
Cependant une des ses consoles rétro a cessé de fonctionner il y a peu, il cherche désormais à s'en procurer une nouvelle via le site, le marché étant relativement restreint pour ce type de produit.  
Au cours de ses recherches, il tombe sur l'annonce de Théo, un jeune homme qui cherche à vendre la vieille console de son père en parfait état, ne connaissant pas beaucoup le marché et ne s'étant pas renseigné, il met un prix très inférieur aux prix habituels pour ce type de produit.
Eudes se connecte et, voyant une opportunité d'économiser une belle somme, se décide à contacter immédiatement Théo en cliquant sur le bouton "me contacter" présent sur l'annonce.  
Après quelques mails envoyés, ils se mettent d'accord pour un rendez-vous dans le but de conclure la vente.  
Quelques jours plus tard, Eudes se rend chez Théo et fait l'acquisition dudit produit, il possède désormais une toute nouvelle console quasiment neuve au détriment du jeune Théo qui pense avoir vendu l'objet à un prix convenable.
Si l'achat est concluant il devra noter le profil du vendeur.

## En résumé

En tant que visiteur,  
Je peux m'inscrire sur le site,  
Afin de contacter un vendeur dans l'optique de réaliser un achat.

## 2. Vendeur
-------------

Guillaume veut vendre ses posters de Francis Lalanne. Il veux publier une annonce sur le site MaBrocrante.Il clique sur déposer une annonce.Comme il n'est pas membre, il dois se créer un profil.
Pour créer son profil le site lui demande via un formulaire plusieurs informations :
  - nom
  - prenom
  - adresse mail
  - mot de passe
Ensuite on lui envoie un mail de confirmation, il clique sur le lien contenu dans cet e-mail pour activer son compte.
Il accède au formulaire pour demande de dépôt d'annonce, il dois saisir plusieurs informations :
- Le nom de l'annonce ou l'objet qu'il vend
- Une description de l'objet la plus complète possible
- Le prix auquel il désire le vendre
- Le lieu où se trouve l'objet
- Si l'objet peut être envoyé ou remis en main propre
- Plusieurs photos (non obligatoire)
- Au minimum un moyen de contact (numéro de téléphone ou adresse e-mail).

Il attend la confirmation d'un modérateur de la validité de l'annonce.
Guillaume sera contacté par mail ou par téléphone par un potentiel acheteur avec lequel ils se mettrons en accord.
Si la vente est concluante il devra supprimer son annonce et noter le profil de l'acheteur.

## En résumé

En tant que visiteur,  
Je peux m'inscrire sur le site,  
Afin de déposer une annonce.

## 3. Modération d'une petite annonce.
------------------------------

Thierry est éditeur et modérateur de MaBrocante et veut contrôler les annonces des utilisateurs et vendeurs.

Il clique sur 'espace de modération'. Il voit la liste des annonces publiées par les vendeurs et pour chacun consulte l'annonce proposée en cliquant dessus.

Si il juge qu'une annonce est correctement renseignée, il clique sur le bouton "Accepter" et elle est maintenant affichée publiquement.

En consultant une seconde annonce, il juge qu'elle commet des manquements à la charte de Ma Brocante et que l'annonce contient des erreurs ne pouvant la faire accepter. Ainsi il précise les détails du refus dans un champ de texte destiné à être envoyé au vendeur, puis clique sur le bouton "Refuser".

### En résumé
En tant que modérateur,  
Je peux accepter ou refuser des annonces en attente de publication  
Afin de publier des annonces conformes à la charte du site.
## III. Cas d'utilisations ##

### 1. Inscription
-------------

Un visiteur peut choisir de s'inscrire sur le site. Pour cela, il va renseigner différentes informations :
* son nom
* sa date de naissance
* son adresse
* ses préférences de zones géographiques de recherche

Cela lui permet d'avoir le champ de recherche pré-rempli sur ses préférences lors de la recherche d'un produit en tant qu'acheteur, ou de pouvoir déposer une annonce en tant que vendeur.  
Par exemple Guillaume, né le 11/09/91 crée son profil en renseignant son adresse en Vendée lors de sa création de compte dans l'intention de vendre aux alentours ses goodies de Francis Lalanne.

### En résumé

En tant que visiteur,  
Je peux m'inscrire sur le site,  
Afin de profiter d'avantages pour la recherche ou le dépôt d'annonce.

### 2. Déposer une annonce
-------------

Le vendeur devra tout d'abord cliquer sur un bouton pour déposer une annonce.  
Puis une fois sur la page de dépôt d'annonce il devra renseigner plusieurs champs afin de fournir le plus de détails sur l'objet qu'il désire vendre, dans notre cas une collection de poster de Francis Lalanne.

![logo](poster.gif)

### Détails à fournir :
    - Le nom de l'annonce ou l'objet qu'il vend
    - Une description de l'objet la plus complète possible
    - Le prix auquel il désire le vendre
    - Le lieu où se trouve l'objet
    - Si l'objet peut être envoyé ou remis en main propre
    - Plusieurs photos (non obligatoire)
    - Au minimum un moyen de contact (numéro de téléphone ou adresse e-mail).

Un fois qu'il aura renseigné tous les champs il devra accepter les CGU de Ma Brocante pour le dépôt d'une annonce et cliquer sur un bouton de validation pour soumettre l'annonce à la modération.  
Le vendeur recevra un e-mail de confirmation de prise en compte de l'annonce ainsi que le temps estimée du traitement de celle-ci par la modération.
Par exemple Guillaume désire déposer une annonce de collection de posters de Francis Lalanne à un prix de 50€ depuis la Vendée. Le produit peut être remis en main propre ou être envoyé. Il laisse également son adresse mail pour être contacté, ainsi que quelques photos.

### En résumé
En tant que vendeur  
Je peux déposer une annonce  
Afin de pouvoir vendre mon objet le plus facilement et rapidement possible.


### 3. Modération d'une petite annonce.
------------------------------

- En tant qu'éditeur du site et modérateur je dois pouvoir contrôler toutes les annonces  des utilisateurs vendeurs avant leur publication sur le site.


Le modérateur de site peut accéder à son espace de modération.  
Une fois qu'une annonce est publiée par un utilisateur, il y a accès dans cet espace afin de la valider, ou non.
Il peut consulter les annonces en attente de validation.

### Acceptation de l'annonce
Je valide les petites annonces correctement renseignées à l'aide d'un simple bouton, l'affichant maintenant publiquement pour les utilisateurs, par exemple l'acceptation de l'annonce tout à fait conforme de Guillaume, qui désire vendre sa collection de posters plutôt sympatoches.

### Refus de l'annonce
En cas de manquement des petites annonces à la charte de Ma Brocante ou en cas d'erreur dans l'annonce, le modérateur peut refuser l'annonce en appuyant sur un bouton. Elle n’apparaît donc pas publiquement et le modérateur peut envoyer un mail à l'utilisateur d'origine pour lui indiquer les raisons de son refus.

### En résumé
En tant que modérateur,  
Je peux accepter ou refuser des annonces en attente de publication  
Afin de publier des annonces conformes à la charte du site.  

### 4. Recherche d'annonce et achat
---------------------

Un visiteur peut choisir de s'inscrire sur le site. Pour cela, il va renseigner différentes informations :
* son nom
* sa date de naissance
* son adresse
* ses préférences de zones géographiques de recherche

Cela lui permet d'avoir le champ de recherche pré-rempli sur ses préférences lors de la recherche d'un produit en tant qu'acheteur, ou de pouvoir déposer une annonce en tant que vendeur.  
Par exemple Guillaume, né le 11/09/91 crée son profil en renseignant son adresse en Vendée lors de sa création de compte dans l'intention de vendre aux alentours ses goodies de Francis Lalanne.

### En résumé

En tant que visiteur,  
Je peux m'inscrire sur le site,  
Afin de profiter d'avantages pour la recherche ou le dépôt d'annonce.

### 5. Système de réputation
---------------------------
Après avoir effectué un achat ou une vente, un e mail est envoyé automatiquement à l'acheteur ou au vendeur pour qu'il note la transaction.
Ce système permettra d'obtenir des récompenses si leur profil a une bonne réputation.

### En résumé  
En tant que membre de MaBrocrante,  
Je peux noté mes transactions,  
Pour assurer les futurs acheteurs/vendeurs sur la réputation de celui-ci et aussi obtenir une récompense.


1. Description du cas d'utilisation ;
2. Diagrammes de CUs.

## Diagrammes des Classes ##

Voici un exemple de diagramme de classe

![Exemple d'image](./1.jpg "Diagramme")


## Packetage ##

Il faut separer les classes en "Packets", selon la méthodologie vue en
cours (par couches, ou par fonctionnalités, etc.)

## Glossaire métier ##

Acheteur : Utilisateur inscrit sur le site ayant pour vocation la consultation ou l'achat d'un produit mis en vente.

Modérateur : Utilisateur inscrit responsable de la validation des annonces soumises sur le site.

Vendeur : Utilisateur inscrit sur le site ayant pour vocation la vente d'un produit sur le site.

Visiteur : Utilisateur lambda qui utilise le site sans être connecté, sans bénéficier des avantages d'un utilisateur inscrit.
