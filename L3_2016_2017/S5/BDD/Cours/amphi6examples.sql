---- BDD Licence Informatique, FIL, Universite Lille1
---- exemples du cours 6 du 5 octobre 2016
-- auteur: Celine Kuttler

---- REMARQUE: nous montrons ici plus de solutions par question qu'en amphi!


------------------------------------------------------------------------------
---articles non fournissables
--- requetes equivalentes

select * from articles where aid <>ALL (select aid from catalogue);

select * from articles where aid NOT IN (select aid from catalogue);

--- a est une "variable de correlation"
select * from articles a where NOT EXISTS (select * from catalogue c where c.aid=a.aid);

-- autre alternative avec EXCEPT (deja fait en TP)



-------------------------------------------------------------------------------
---l'article le moins cher
--- requetes equivalentes

select * from catalogue where prix <= ALL (select prix from catalogue);

select * from catalogue c where NOT EXISTS (select * from catalogue c2 where c2.prix < c.prix);

select * from catalogue where prix = (select min(prix) from catalogue);


---------------------------------------------------------------------------------
--- articles avec au moins 2 fournisseurs
--- requetes equivalentes:

select aid from catalogue group by aid having count(distinct fid) >= 2;

-- vu en amphi
select  aid 
from catalogue c1 
where exists (select * from catalogue c2 where c1.aid=c2.aid and c1.fid<>c2.fid) ;


select aid 
from catalogue c 
where  fid <> some(select fid from catalogue c2 where c2.aid=c.aid);
--- le style de cette requete n'est pas a recommander! l'utilisation d'une variable de correlation c dans la sous-requete avec SOME est lourde.


-- la plus facile
select distinct c1.aid 
from catalogue c1 , catalogue c2 
where c2.aid=c1.aid and  c2.fid<>c1.fid;

--------------------------------------------------------------------------------
--- vendeur offrant aussi bien du  rouge que du vert


select fid
from catalogue c natural join articles
where acoul='vert'
and EXISTS (
    select * 
    from catalogue c2 natural join articles 
    where acoul='rouge'
    and c2.fid=c.fid
);


select fid
from catalogue join articles using aid
where acoul='vert' and
      fid = SOME (select fid from catalogue natural join articles where acoul='rouge');


select fid
from catalogue natural join articles
where acoul='vert' and
      fid IN (select fid from catalogue natural join articles where acoul='rouge');

(select fid
from catalogue natural join articles
where acoul='vert')
INTERSECT
(select fid
from catalogue natural join articles
where acoul='rouge');

--------------------------------------------------------------------------
------  monopolistes et leur articles

select fid,aid from catalogue c
where NOT EXISTS
      (select * from catalogue c2 
      where c2.aid=c.aid and c2.fid<>c.fid);
---- comparez avec: "article avec 2 vendeurs! (version EXISTS)"


