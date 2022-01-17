# BDA TP3 - CouchDB
## https://www.paperman.name/page/enseignement/2021/nosql/TD3.html


# VM
- redis-1: 172.28.101.85 (POSTGRE)
- redis-2: 172.28.100.172


# Part I
### Q4: Comment intégrer votre fonction tag au middleware pour garantir que les tags soient insérés dynamiquement?
On peut introduire les tags lors de l'insertion des articles

# Part II
```postgresql
article=# select pyenv();
                      pyenv                      
-------------------------------------------------
 pwd: /var/lib/postgresql/12/main user: postgres
(1 row)
```
L'exécution des scripts ce fait à partir du dossier /var/lib/postgresql/12/main et avec l'utilsateur de la BDD (postgres)

### Q4: Activer le timing dans psql à l’aide de la commande \timing on. Comparer le temps d’exécution d’une requête SQL la plus simple possible avec le temps d’exécution pyenv. Estimez le surcout d’un appel à une fonction Python.

```postgresql
article=# select pyenv();
                      pyenv                      
-------------------------------------------------
 pwd: /var/lib/postgresql/12/main user: postgres
(1 row)

Time: 62.870 ms
article=# select * from articles where article_id='c203a4e8-3c96-11ec-b2e5-832b4cc7abf1';
Time: 4.989 ms
```
On remarque un facteur de x12 entre pyenv et une requête SELECT.

