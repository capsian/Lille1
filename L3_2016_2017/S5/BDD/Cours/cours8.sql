---

----vendeur n'offrant aucun article vert
---1: avec SOME

select f.fnom
from fournisseurs f 
where not  ('vert'=SOME (select acoul from articles join catalogue c using (aid) where c.fid=f.fid));



---2: avec in

select f.fnom
from fournisseurs f
where 'vert' NOT IN  (select acoul from articles join catalogue using (aid) where fid=f.fid);

select fnom
from fournisseurs 
where fid NOT IN (select fid from articles join catalogue using (aid) where acoul='vert');


      
---3: avec group by

select fnom
from (fournisseurs join catalogue using (fid)) join articles using (aid)
group by fnom
having  EVERY (acoul <> 'vert');

--- synonyme pour EVERY: bool_and
--- l'operateur teste si le ET logique et vrai pour tous les cas, 
---- donc ici pour tous les articles du fornisseur en question.
---- un operateur similaire bool_or existe, il n'a pas de synonyme.

--- dans cette requete, le vendeur HappyCake n'apparait pas. Il n'offre aucun article. 
-- Il est discutable si on devrait, ou non, vraiment l'avoir dans le resultat des autres requetes.
--- pour ne pas l'avoir, il suffit dans toutes les clauses FROM d'ajouter une jointure avec le catalogue.

---4: avec ALL
select f.fnom
from fournisseurs f
where  'vert'<> ALL (select acoul from articles join catalogue using (aid) where fid=f.fid);



