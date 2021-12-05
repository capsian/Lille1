## Compte rendu TP Bandit:
Auteurs: **Akeniouene Abderrahmane & Boutaleb Fouad**

### Première version
---
![Regrets/Rewards with random method](plots/Figure_2.png)

On peut voir que le regret progresse plus vite que le reward sur notre `horizon` de 10000 et sur `100` expériences.

### Version de travail
---
![Regrets/Rewards with random method](plots/Figure_4.png)

On peut remarquer que sur les 100 eperiences, les regrets et les rewards suivent plus ou moins la même trajectoire d'une experience à une autre.


### Stratégies gloutonnes
---

![Regrets/Rewards with random method](plots/Figure_3.png)

La courbe des regrets suivant la stratégie gloutonne progresse moins vite quand `epsilon` vaut `0.1`, car on fait plus d'exploitation que d'exploration.


### Stratégie de Boltzmann
---

![Regrets/Rewards with random method](plots/Figure_5.png)

Plus la valeur de `tau` est petite plus la progression des regrets augmonte plus vite.



### Stratégie optimiste
---
![Regrets/Rewards with random method](plots/Figure_6.png)

Ici, avec alpha valant `0.5`, donne de meilleurs résultats que les deux autres valeurs.


### Comparaison générale
---
![Regrets/Rewards with random method](plots/Figure_1.png)

La méthode la plus satisfaisante est **Thompson**, suivie par **UCB**.
la methode gloutonne a été parametrée avec `epsilon` valant `0.5`, donc mi-exploitation, mi-exploration, si jamais on l'initialise à `1`, sa courbe sera equivalente à celle de la méthode aléatoire.
Pour la **Proportionnelle** et **Boltzmann**, elles suivent plus ou moins l'**Aléatoire**.
