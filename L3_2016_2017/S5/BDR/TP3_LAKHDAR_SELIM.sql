--Q1/ Facile
SELECT anom AS ARTICLE, COUNT(acoul) AS NB_COUL FROM Articles GROUP BY anom;

--Q2/ Facile
SELECT anom AS ARTICLE, max(prix) AS PRIX_MAX, min(prix) AS PRIX_MIN, count(DISTINCT(fid)) AS NB_FOURNISSEUR FROM Catalogue JOIN Articles ON Articles.aid=Catalogue.aid GROUP BY anom HAVING count(DISTINCT(fid))>1; 

--Q3/ Moyen
SELECT acoul AS COULEURS_RARES FROM Articles 
GROUP BY acoul 
HAVING COUNT(anom) = 1

--Q4/ Moyen
SELECT acoul AS COULEUR, AVG(prix) AS PRIX_MOYEN FROM Catalogue
NATURAL JOIN Articles
WHERE aid <> 11
GROUP BY acoul
HAVING COUNT(fid) > 1
ORDER BY PRIX_MOYEN DESC

--Q5/ Facile
SELECT anom, acoul, COUNT(fid) FROM Catalogue
NATURAL JOIN Articles
GROUP BY anom,acoul
HAVING COUNT(fid) >=1 

--Q6/ Facile
SELECT anom, COUNT(DISTINCT(fid)) FROM Catalogue C
FULL JOIN Articles A ON A.aid=C.aid
GROUP BY anom

--Q7/ Moyen
SELECT fnom AS FOURNISSEURS, COUNT(DISTINCT(anom)) AS NB_A FROM Catalogue C
NATURAL JOIN Fournisseurs NATURAL JOIN Articles
GROUP BY fnom
HAVING COUNT(C.aid) > 1

--Q8/ Moyen
SELECT fnom, anom FROM Fournisseurs 
NATURAL JOIN Catalogue NATURAL JOIN Articles 
GROUP BY fnom, anom 
HAVING count(*) > 1

--Q9/ Moyen
SELECT anom FROM Articles
JOIN Catalogue C USING(aid)
GROUP BY anom
HAVING COUNT(fid) = 1

--Q10/ Moyen
SELECT distinct(substring(anom,1,1)), count(substring(anom,1,1)) From Articles
GROUP BY anom

--Q11/ Facile
SELECT distinct(substring(acoul,1,1)), count(substring(acoul,1,1)) From Articles
GROUP BY acoul

--Q12/
-- On utilise USING la jointure se fait sur des colones qui ont le meme nom
-- On utilise ON lorsque la jointure se fait sur des colones qui n'ont pas le meme nom
