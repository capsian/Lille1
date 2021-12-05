Retour Rendu 2
==============

# Diagrammes de Classes (DC)

- Manque une flèche entre Membre et Modérateur
- Interface Produit encore à changer en classe abstraite. Quels sont les fils ? Y a-t-il des sous-classes ?
- Qui implémente l'interface Catégorie ? Quelles sont les catégories possibles ? Quelles sont les méthodes à implémenter ?
- Flèche d'Annonce à Membre
- Association entre Annonce et Catégorie : ne rien mettre à la place du losange, c'est une association simple.
- Catégorie : Juste un label ? -> enum
- Séparer le contrôleur et le modèle.
- Rajouter la classe Message et ce qui tourne autour. Est-ce que l'on peut consulter la liste des messages reçus ? L'historique ? Les réponses ?

# Cas d'Utilisations

- Pas de CU pour la réputation/les récompenses

# Diagrammes de Séquences (DS)

- Si l'on peut voir ListeAnnonces dans le DS, il doit l'être aussi dans le DC, en composition avec toutes les annonces du système.
- Modifier une annonce : passer par la liste d'annonces

# Classement des cas d'usages

 - Explication pour chaque note, pour chaque classification.
 - Noter le profil : revoir priorité

# Notes du vrac

- Partie intéressante : réputation/récompenses à développer.
- Profil/Membre : Pas clair. Redondance ? -> Conserver une seule liste.

# Pour la prochaine séance

- Maquettage et paquetage
- Réduire les liens et dépendances d'un paquet à l'autre
- Etoffer le glossaire métier, actuellement trop pauvre, avec les classes Annonce, Message (les classes du domaine, sans forcément les compositions, comme ListeAnnonces, ou ListeMessages)

# Conclusion

- Rendu correct mais un soucis avec le DC, il manque la taxonomie, les liens entre les DC, et des confusions sont présentes (Liste membres/profils).
- Rendu minimaliste, les choses un peu intéressantes n'ont pas été développées.
