-- correction TD Indexation

----------------
-- Exercice 1 --
----------------
-- question 1.1
/*
Nom : facture_pkey
Définition : CREATE UNIQUE INDEX facture_pkey ON facture USING btree (fac_num)
Contraintes : Clé primaire
En cluster ? : Non
*/

-- question 1.2
-- on vérifie que l'index est utilisé
explain select fac_num, fac_date, fac_montant
from facture
where fac_num = 500;

/*
Index Scan using facture_pkey on facture  (cost=0.28..8.29 rows=1 width=15)
  Index Cond: (fac_num = '500'::numeric)
*/

-- ou bien avec en plus comparaison estimation/exécution
explain analyze select fac_num, fac_date, fac_montant
from facture
where fac_num = 500;

/*
Index Scan using facture_pkey on facture  (cost=0.28..8.29 rows=1 width=15) (actual time=0.126..0.130 rows=1 loops=1)
  Index Cond: (fac_num = '500'::numeric)

Planning Time: 0.483 ms
Execution Time: 0.149 ms
*/

-- explain requete donne le plan d'exécution sans exécuter la requête
-- explain analyze requete donne le plan ET exécute la requête

/* comparaison coût estimé/réel :
Note that the “actual time” values are in milliseconds of real time,
whereas the cost estimates are expressed in arbitrary units;
so they are unlikely to match up.
The thing that's usually most important to look for is whether the estimated row counts
are reasonably close to reality.
*/

-- question 1.3
-- si on applique une fonction sur la colonne indexée, on ne peut plus utiliser l'index

-- ça peut être piégeux,
-- Pour y remédier, passer les opérateurs du côté du litéral quand c'est possible,
-- ou trouver une expression équivalente sans toucher à la colonne indexée
-- par exemple remplacer :
explain select fac_num, fac_date, fac_montant
    from facture
    where floor(fac_num/100) = 5 ;

/*
Seq Scan on facture  (cost=0.00..61.56 rows=10 width=15)
  Filter: (floor((fac_num / '100'::numeric)) = '5'::numeric)
*/

-- par :
explain select fac_num, fac_date, fac_montant
from facture
where fac_num between 500 and 599;

/*
Index Scan using facture_pkey on facture  (cost=0.28..11.28 rows=100 width=15)
  Index Cond: ((fac_num >= '500'::numeric) AND (fac_num <= '599'::numeric))
*/

-- Remarquer au passage que cette seconde requête est une "range query",
-- et un index B-arbre peut être utilisé dans ce cas

-- question 1.4
-- Qu'est-ce qui se passe si on combine 2 conditions, dont une sur la clé primaire ?
explain select fac_num, fac_date, fac_montant
from facture
where fac_date between to_date('2017-06-01','YYYY-MM-DD') and to_date('2017-08-31','YYYY-MM-DD')
and fac_num between 500 and 550;

/*
Index Scan using facture_pkey on facture  (cost=0.28..9.81 rows=13 width=15)
  Index Cond: ((fac_num >= '500'::numeric) AND (fac_num <= '550'::numeric))
  Filter: ((fac_date >= to_date('2017-06-01'::text, 'YYYY-MM-DD'::text)) AND (fac_date <= to_date('2017-08-31'::text, 'YYYY-MM-DD'::text)))
*/

-- remarque : le to_date n'est pas obligatoire
explain select fac_num, fac_date, fac_montant
from facture
where fac_date between '2017-06-01' and '2017-08-31'
and fac_num between 500 and 550;

/*
Index Scan using facture_pkey on facture  (cost=0.28..9.55 rows=13 width=15)
  Index Cond: ((fac_num >= '500'::numeric) AND (fac_num <= '550'::numeric))
  Filter: ((fac_date >= '2017-06-01'::date) AND (fac_date <= '2017-08-31'::date))
*/

----------------
-- Exercice 2 --
----------------
-- question 2.1
-- on revient sur la requête "factures dont le numéro est entre 500 et 599"
-- hash index sur une expression
create index factures_par_centaine_hash on facture using hash(floor(fac_num/100)) ;
-- la sélectivité est de 1 pour 100 (1 entrée pour 100 lignes de la table)

-- question 2.2
explain analyze
select fac_num, fac_date, fac_montant
    from facture
    where floor(fac_num/100) = 5 ;

/*
Bitmap Heap Scan on facture  (cost=4.08..24.37 rows=10 width=15) (actual time=0.099..0.341 rows=100 loops=1)
  Recheck Cond: (floor((fac_num / '100'::numeric)) = '5'::numeric)
  Heap Blocks: exact=2
  ->  Bitmap Index Scan on factures_par_centaine_hash  (cost=0.00..4.08 rows=10 width=0) (actual time=0.066..0.068 rows=100 loops=1)
        Index Cond: (floor((fac_num / '100'::numeric)) = '5'::numeric)

Planning Time: 0.373 ms
Execution Time: 0.546 ms
*/

drop index factures_par_centaine_hash;
-- btree index sur la même expression
create index factures_par_centaine on facture using btree(floor(fac_num/100)) ;

-- même requête, même plan entre un hash-index et un btree (parce que requête sur 1 valeur de clé)
/*
Bitmap Heap Scan on facture  (cost=4.36..24.64 rows=10 width=15) (actual time=0.084..0.268 rows=100 loops=1)
  Recheck Cond: (floor((fac_num / '100'::numeric)) = '5'::numeric)
  Heap Blocks: exact=2
  ->  Bitmap Index Scan on factures_par_centaine  (cost=0.00..4.35 rows=10 width=0) (actual time=0.055..0.057 rows=100 loops=1)
        Index Cond: (floor((fac_num / '100'::numeric)) = '5'::numeric)

Planning Time: 0.511 ms
Execution Time: 0.487 ms
*/

drop index factures_par_centaine ;

-- range query avec l'index unique sur la clé primaire
explain analyze select fac_num, fac_date, fac_montant
from facture
where fac_num between 500 and 599;

/*
Index Scan using facture_pkey on facture  (cost=0.28..11.28 rows=100 width=15) (actual time=0.107..0.294 rows=100 loops=1)
  Index Cond: ((fac_num >= '500'::numeric) AND (fac_num <= '599'::numeric))

Planning Time: 0.408 ms
Execution Time: 0.494 ms
*/

-- REMARQUE : Postgres n'est pas très bon avec les estimations quand on utilise l'index sur la fonction
-- Il s'attend à 10 lignes au lieu de 100.

/*
Index Scan vs Bitmap index scan/bitmap heap scan/recheck cond
"a plain Index Scan fetches one tuple-pointer at a time from the index, and immediately visits that tuple
in the table. A bitmap scan fetches all the tuple-pointers from the index in one go,
sorts them using an in-memory "bitmap" data structure, and then visits the table tuples
in physical tuple-location order." (Tom Lane)
*/


-- Pas demandé :
-- création d'un index par millier de fac_num
create index factures_par_millier on facture using btree(floor(fac_num/1000)) ;

explain analyze
select fac_num, fac_date, fac_montant
    from facture
    where floor(fac_num/1000) = 1 ;

-- l'index reste utilisé malgré une sélectivité plus faible (1 pour 1000)
-- il pense toujours que le résultat va contenir 10 lignes.
/*
Bitmap Heap Scan on facture  (cost=4.36..24.64 rows=10 width=15) (actual time=0.174..2.016 rows=1000 loops=1)
  Recheck Cond: (floor((fac_num / '1000'::numeric)) = '1'::numeric)
  Heap Blocks: exact=8
  ->  Bitmap Index Scan on factures_par_millier  (cost=0.00..4.35 rows=10 width=0) (actual time=0.145..0.147 rows=1000 loops=1)
        Index Cond: (floor((fac_num / '1000'::numeric)) = '1'::numeric)

Planning Time: 0.420 ms
Execution Time: 3.729 ms
*/

-- question 2.3
-- création d'un index sur la date de la facture
create index factures_ordre_chronologique on facture(fac_date) ;
-- ou bien
-- CREATE INDEX factures_ordre_chronologique ON facture USING btree(fac_date)

-- question 2.4
create index factures_par_mois_hash on facture using hash(date_trunc('month',fac_date)) ;
--> erreur "les fonctions dans l'expression de l'index doivent être marquées comme IMMUTABLE"
-- Le problème vient du fait que le temps est relatif à la configuration du serveur
-- Selon le fuseau horaire, la date stockée peut changer de jour (à 1 journée près)
-- Il faut donc préciser le fuseau dans l'index ... et dans la requête, ce qui est pénible.

create index factures_par_mois_hash on facture using hash(to_char(fac_date,'MM')) ;
--> même problème. C'est logique

-- Dans mon exemple j'essaie de créer un hash-index, c'est le même message avec un BTree (il n'y  a pas de raison que ça change).

-- question 2.5
-- ici, il faut faire attention à ne pas utiliser de fonction
explain analyze
select * from facture
where date_trunc('month',fac_date) = '2017_04_01'

/*
Seq Scan on facture  (cost=0.00..61.56 rows=10 width=15) (actual time=0.304..1.070 rows=187 loops=1)
  Filter: (date_trunc('month'::text, (fac_date)::timestamp with time zone) = '2017-04-01 00:00:00+00'::timestamp with time zone)
  Rows Removed by Filter: 1845
Planning Time: 0.324 ms
Execution Time: 1.391 ms
*/

-- mais plutôt une range query
explain analyze
select * from facture
where fac_date between '2017_04_01' and '2017_04_30'

/*
Index Scan using factures_ordre_chronologique on facture  (cost=0.28..14.06 rows=189 width=15) (actual time=0.043..0.409 rows=187 loops=1)
  Index Cond: ((fac_date >= '2017-04-01'::date) AND (fac_date <= '2017-04-30'::date))
Planning Time: 0.377 ms
Execution Time: 0.728 ms
*/

----------------
-- Exercice 3 --
----------------

/*
A multicolumn B-tree index can be used with query conditions that involve any subset of the index's columns,
but the index is most efficient when there are constraints on the leading (leftmost) columns.
The exact rule is that equality constraints on leading columns, plus any inequality constraints on the first column
that does not have an equality constraint, will be used to limit the portion of the index that is scanned.
Constraints on columns to the right of these columns are checked in the index, so they save visits to the table proper,
but they do not reduce the portion of the index that has to be scanned.
For example, given an index on (a, b, c) and a query condition WHERE a = 5 AND b >= 42 AND c < 77,
the index would have to be scanned from the first entry with a = 5 and b = 42 up through the last entry with a = 5.
Index entries with c >= 77 would be skipped, but they'd still have to be scanned through.
This index could in principle be used for queries that have constraints on b and/or c with no constraint on a
— but the entire index would have to be scanned,
so in most cases the planner would prefer a sequential table scan over using the index.
*/

-- question 3.1

-- quand les 2 colonnes sont connues, on utilise l'index comme d'habitude (index scan avec condition sur la valeur de la clé)
explain analyze select * from ligne_facture
where lig_facture = 250 and lig_produit = 44 ;
/*
Index Scan using ligne_facture_pkey on ligne_facture  (cost=0.28..8.30 rows=1 width=21) (actual time=0.049..0.051 rows=0 loops=1)
  Index Cond: ((lig_facture = '250'::numeric) AND (lig_produit = '44'::numeric))
Planning Time: 0.556 ms
Execution Time: 0.073 ms
*/

-- idem pour un intervalle
explain select * from ligne_facture
where lig_facture between 1000 and 1005 ;
/*
Bitmap Heap Scan on ligne_facture  (cost=4.36..21.37 rows=8 width=21)
  Recheck Cond: ((lig_facture >= '1000'::numeric) AND (lig_facture <= '1005'::numeric))
  ->  Bitmap Index Scan on ligne_facture_pkey  (cost=0.00..4.36 rows=8 width=0)
        Index Cond: ((lig_facture >= '1000'::numeric) AND (lig_facture <= '1005'::numeric))
*/

-- ici l'index ne sert pas parce que la condition porte sur la 2nde colonne
explain select * from ligne_facture
where lig_produit = 44 ;
/*
Seq Scan on ligne_facture  (cost=0.00..72.60 rows=86 width=21)
  Filter: (lig_produit = '44'::numeric)
*/

-- question 3.2

/*
--1- index sur (col1, col2)
efficace quand la requête met des conditions sur col1 et col2, ou sur col1 (dans une moindre mesure)
Pas utilisé (ou très rarement) quand il s'agit d'une requête sur col2 seul.
Il suffit de prendre l'exemple d'un répertoire téléphonique pour s'en convaincre.
Si on a rangé selon (nom, prénom),
on est obligé de regarder toutes les lettres pour rechercher une "Marion"

--2- index sur col1 et index sur col2
efficace quand la requête met une condition sur col1, ou sur col2.
On peut s'en sortir quand conditions sur les 2 colonnes, en faisant l'intersection des ensembles de lignes.
Attention, 2 indexes sont plus coûteux à maintenir qu'un seul.

Comme dit dans la remarque qui suit la question 3.2 dans le sujet,
on ne va pas en général au delà de 2 colonnes pour un index composite.
Sauf cas d'utilisation spécifique, comme en décisionnel,
avec un modèle en étoile et une table de faits (i.e. le coeur de l'étoile) qui a beaucoup de clés étrangères.
Dans ce cas on choisit en général le Temps comme col1,
pour que la mise à jour de l'index soit facilitée par des alimentations
de la table qui se font par ordre chronologique (e.g. insertion de nouvelles lignes chaque jour).
*/

----------------
-- Exercice 4 --
----------------
-- question 4.1
-- dans la requête suivante, seul l'index est lu, pas besoin d'accéder ensuite aux lignes de la table
-- c'est le sens du Index Only Scan
explain analyze select count(*)
from facture
where fac_num between 500 and 550;

/*
Aggregate  (cost=9.42..9.43 rows=1 width=8) (actual time=2.755..2.761 rows=1 loops=1)
  ->  Index Only Scan using facture_pkey on facture  (cost=0.28..9.30 rows=51 width=0) (actual time=2.474..2.637 rows=51 loops=1)
        Index Cond: ((fac_num >= '500'::numeric) AND (fac_num <= '550'::numeric))
        Heap Fetches: 51

Planning Time: 0.513 ms
Execution Time: 2.858 ms
*/

-- question 4.2
-- ALBUM est une petite table :
select pg_size_pretty(pg_table_size('music.album'));
--8192 bytes
select pg_size_pretty(pg_indexes_size('music.album'));
--16Ko

explain analyze select *
from album
where al_id=20;
/*
Seq Scan on album  (cost=0.00..1.62 rows=1 width=22) (actual time=0.026..0.032 rows=1 loops=1)
  Filter: (al_id = '20'::numeric)
  Rows Removed by Filter: 49

Planning Time: 0.423 ms
Execution Time: 0.057 ms
*/
--> on perd du temps à lire l'index, puisque ça oblige à lire des blocs supplémentaires.

-- question 4.3
explain select lig_facture, sum(lig_quantite) as nb_produits, count(*) as nb_produits_distincts
from ligne_facture
group by lig_facture;
/*
HashAggregate  (cost=91.64..117.04 rows=2032 width=45)
  Group Key: lig_facture
  ->  Seq Scan on ligne_facture  (cost=0.00..63.08 rows=3808 width=10)
*/

/*
Parenthèse sur HashAggregate :
On remplit une table de hashage pour fabriquer les groupes.
L'avantage est qu'on n'a pas besoin de trier les lignes de la table mais l'inconvénient est la place que ça prend en mémoire.
*/

explain select lig_facture, sum(lig_quantite) as nb_produits, count(*) as nb_produits_distincts
from ligne_facture
where lig_facture between 500 and 550
group by lig_facture;
/*
HashAggregate  (cost=32.39..33.57 rows=94 width=45)
  Group Key: lig_facture
  ->  Bitmap Heap Scan on ligne_facture  (cost=5.25..31.68 rows=95 width=10)
        Recheck Cond: ((lig_facture >= '500'::numeric) AND (lig_facture <= '550'::numeric))
        ->  Bitmap Index Scan on ligne_facture_pkey  (cost=0.00..5.23 rows=95 width=0)
              Index Cond: ((lig_facture >= '500'::numeric) AND (lig_facture <= '550'::numeric))
*/

-- si le filtre n'est pas assez sélectif, on n'utilise plus l'index
explain select lig_facture, sum(lig_quantite) as nb_produits, count(*) as nb_produits_distincts
from ligne_facture
where lig_facture between 200 and 1000
group by lig_facture;

/*
HashAggregate  (cost=93.09..108.25 rows=1213 width=45)
  Group Key: lig_facture
  ->  Seq Scan on ligne_facture  (cost=0.00..82.12 rows=1463 width=10)
        Filter: ((lig_facture >= '200'::numeric) AND (lig_facture <= '1000'::numeric))
*/

-- Pour choisir le plan d'exécution : estimation du nombre de blocs que l'on va devoir lire pour répondre à la requête
-- Il faut compter les blocs de l'index PLUS les blocs de la table.
-- Si cette somme dépasse le nombre total de blocs de la table, autant faire un Scan sans lire l'index.

----------------
-- Exercice 5 --
----------------
create index ligne_facture_par_prod
on ligne_facture(lig_produit)
where lig_quantite > 1 ;
-- il n'y a que 14 lignes indexées

-- question 5.1
explain analyze select lig_facture, lig_produit, lig_quantite
from ligne_facture
where lig_quantite > 1 ;

/*
Bitmap Heap Scan on ligne_facture  (cost=8.21..30.49 rows=14 width=15) (actual time=0.036..0.067 rows=14 loops=1)
  Recheck Cond: (lig_quantite > '1'::numeric)
  Heap Blocks: exact=10
  ->  Bitmap Index Scan on ligne_facture_par_prod  (cost=0.00..8.21 rows=14 width=0) (actual time=0.028..0.029 rows=14 loops=1)

Planning Time: 0.324 ms
Execution Time: 0.122 ms
*/

-- question 5.1 bis
explain analyze select lig_facture, lig_produit, lig_quantite
from ligne_facture
where lig_quantite > 2 ;

-- le moteur SQL repère bien qu'il peut utiliser l'index
/*
Bitmap Heap Scan on ligne_facture  (cost=8.21..30.49 rows=3 width=15) (actual time=0.040..0.155 rows=3 loops=1)
  Recheck Cond: (lig_quantite > '1'::numeric)
  Filter: (lig_quantite > '2'::numeric)
  Rows Removed by Filter: 11
  Heap Blocks: exact=10
  ->  Bitmap Index Scan on ligne_facture_par_prod  (cost=0.00..8.21 rows=14 width=0) (actual time=0.014..0.016 rows=14 loops=1)

Planning Time: 0.479 ms
Execution Time: 0.198 ms
*/

-- question 5.2
explain analyze select distinct lig_produit
from ligne_facture
where lig_quantite > 1 ;

-- seul l'index est utilisé
-- puisque c'est un index sur lig_produit pour lig_quantite >1
/*
Unique  (cost=0.14..8.33 rows=10 width=5) (actual time=0.040..0.101 rows=11 loops=1)
  ->  Index Only Scan using ligne_facture_par_prod on ligne_facture  (cost=0.14..8.30 rows=11 width=5) (actual time=0.035..0.055 rows=11 loops=1)
        Heap Fetches: 0
Planning Time: 0.538 ms
Execution Time: 0.169 ms
*/

----------------
-- Exercice 6 --
----------------
explain analyze select fac_num, fac_montant
from facture
where fac_num between 100 and 150;

/*
Index Scan using facture_pkey on facture  (cost=0.28..9.41 rows=50 width=11) (actual time=0.014..0.096 rows=50 loops=1)

  Index Cond: ((fac_num >= '100'::numeric) AND (fac_num <= '150'::numeric))

Planning Time: 0.679 ms
Execution Time: 0.198 ms
*/

create index facture_num_include_montant
on facture(fac_num)
include(fac_montant);

explain analyze select fac_num, fac_montant
from facture
where fac_num between 100 and 150;
/*
Index Only Scan using facture_num_include_montant on facture  (cost=0.28..9.41 rows=50 width=11) (actual time=0.016..0.118 rows=50 loops=1)

  Index Cond: ((fac_num >= '100'::numeric) AND (fac_num <= '150'::numeric))

  Heap Fetches: 50

Planning Time: 0.833 ms
Execution Time: 0.228 ms
*/
