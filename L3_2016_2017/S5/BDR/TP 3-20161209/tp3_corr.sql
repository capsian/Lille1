-- TP 3 (2016-17)

----- estimation de difficulte: 
--f--   facile
--m-- moyen
--d--  difficile





--- Q 1
--f -- par article (nom d'article!), le nombre de couleurs  dans lequel l'article est decliné
select  anom as ARTICLE , count (distinct acoul) as NB_COUL
from articles
group by anom ;


--- Q 2
--m - -- noms des articles fournissables, 
-- avec prix maximal et minimal, 
-- uniquement pour les articles avec plus d'un vendeur

select  anom,  min(prix), max(prix), count(distinct fid) as "NB_F", count(distinct acoul) as "NB_C", count(*) as "TOUT"
from articles , catalogue 
where articles.aid=catalogue.aid 
group by articles.anom 
having count(distinct fid)>1;




--- Q 3
--m-- les couleurs "rares", pour lesquelles il n'y a qu'un  seul article 
select acoul as CouleursRares
from articles
group by acoul
having count(*) = 1;




--- Q 4 
--m-- par couleur, sous condition que plus d'un article ce cette couleur soit fournissable,le prix moyen, en excluant la ferrari rouge.
-- trier  par prix moyen decroissant
select  acoul as Couleur , avg (prix) as PrixMoyen 
from articles, catalogue
where articles.aid=catalogue.aid and anom not like 'Ferrari%'
group by acoul 
having count (distinct articles.aid) > 1
order by avg(prix) desc;



--- Q5
--f-- par article fournissable, et par couleur de l'article, 
-- le  nombre de vendeurs offrant l'article dans cette couleur

select  anom , acoul, count( distinct fid) as "nombre de fournisseurs" 
from articles , catalogue 
where articles.aid=catalogue.aid 
group by articles.anom,  articles.acoul; 


--- Q6 
---m - par article, toutes couleurs confondues, le nombre de fournisseurs (meme si zero)

select  anom as "ARTICLE", count(distinct  fid)   as "NB_F"
from articles left join catalogue       
on articles.aid=catalogue.aid                                               
 group by articles.anom                                                      
;





--- Q7
--m- les noms des vendeurs offrant  plus d'un article , et le nombre d'articles qu'ils vendent

select fnom as Fournisseur , count(distinct anom) as NbArticles
from catalogue c, fournisseurs f, articles a
where c.fid=f.fid and a.aid=c.aid
group by c.fid,fnom
having count (distinct anom) >1;


--- Q8
---m-- selectionner les ids des vendeurs qui vendent un meme 
---article en differentes couleurs

select  fnom as "FOURNISSEUR", anom as "ARTICLE", count(acoul) as "NB_COUL"
from articles natural join catalogue natural join fournisseurs f
group by fnom, anom
having count (*) > 1;




--- Q 9
---m-- selectionnner les noms des articles offerts par un seul vendeur, toutes couleurs confondues
-- nice!

select  anom
from articles a,  catalogue c, fournisseurs f
where a.aid = c.aid and c.fid=f.fid
group by anom
having count (distinct fnom) =1;

select a.anom 
from articles a,catalogue c
where 
a.aid=c.aid and 
not exists 
(
select * from catalogue c2,articles a2 
where 
c2.aid=a2.aid
and c2.fid<>c.fid
and a2.anom=a.anom
);


--- Q10
select substring(upper(string(acoul)) from 1 for 1) as Lettre , count(distinct anom) from articles group by Lettre order by Lettre;


