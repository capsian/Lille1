--Q1
SELECT A1.anom FROM Articles A1
WHERE NOT EXISTS (
	SELECT * FROM Articles A2
	WHERE A1.anom = A2.anom AND A1.acoul <> A2.acoul)
	
--Q2
SELECT A1.anom FROM Articles A1
WHERE A1.acoul='rouge' AND NOT EXISTS (
	SELECT * FROM Articles A2
	WHERE A1.anom=A2.anom AND A2.acoul = 'vert')
--
SELECT A1.anom FROM Articles A1
WHERE A1.acoul='rouge' AND A1.anom NOT IN (
	SELECT A2.anom FROM Articles A2
	WHERE A1.anom=A2.anom AND A2.acoul = 'vert')
--
SELECT A1.anom FROM Articles A1
WHERE A1.acoul='rouge' AND A1.acoul = ALL (
	SELECT A2.anom FROM Articles A2
	WHERE A1.anom=A2.anom AND A2.acoul = 'vert')
	
--Q3
SELECT F1.fnom,A1.anom FROM Fournisseurs F1
NATURAL JOIN Catalogue C1 NATURAL JOIN Articles A1
WHERE C1.prix > ALL (
	SELECT AVG(C2.prix) FROM Catalogue C2
	WHERE C1.aid=C2.aid)

--Q4
SELECT DISTINCT(A1.anom) FROM Articles A1
NATURAL JOIN Catalogue C1
WHERE EXISTS (
	SELECT * FROM Catalogue C2
	WHERE C1.aid = C2.aid AND C1.fid <> C2.fid)

--Q5
--IN
SELECT F1.fnom FROM Fournisseurs F1
WHERE F1.fid NOT IN (
	select C1.fid FROM Catalogue C1)
--ALL
SELECT F1.fnom FROM Fournisseurs F1
WHERE F1.fid <> ALL (
	SELECT C1.fid FROM Catalogue C1)
	
--Q6
SELECT A1.anom FROM Articles A1
NATURAL JOIN Catalogue C1
WHERE NOT EXISTS (
	SELECT * FROM Catalogue C2
	WHERE C1.fid <> 1)
	
--Q7
SELECT F.* FROM Fournisseurs F
WHERE NOT EXISTS(
	SELECT * FROM Articles A
	WHERE NOT EXISTS(
		SELECT * FROM Catalogue C
		WHERE C.fid = F.fid AND C.aid = A.aid))
		
--Q8
SELECT F1.fnom FROM Fournisseurs F1
NATURAL JOIN Catalogue C1
WHERE NOT EXISTS (
	SELECT * FROM Catalogue C2
	WHERE C1.prix < C2.prix)
	
--Q9
SELECT anom, MIN(prix), MAX(prix),aid FROM Articles
NATURAL JOIN Catalogue
GROUP BY anom,aid
HAVING COUNT(DISTINCT(fid))>1
--
SELECT A1.anom, min(C1.prix) as "prix_min", max(C1.prix) as "prix_max"
FROM Articles A1 NATURAL JOIN  Catalogue C1
WHERE EXISTS(
	SELECT *
	FROM Catalogue C2
 	WHERE C2.fid <> C1.fid and A1.aid = C2.aid)
GROUP BY A1.anom;
--

	
--Q10
SELECT DISTINCT(F1.fnom), A1.anom FROM Catalogue C1
NATURAL JOIN Fournisseurs F1 NATURAL JOIN Articles A1
WHERE EXISTS (
	SELECT * FROM Catalogue C2
	NATURAL JOIN Articles A2
	WHERE A1.anom = A2.anom AND A1.acoul <> A2.acoul AND C1.fid = C2.fid)
	
--Q11
	-- not exists
SELECT DISTINCT(A1.anom) FROM Catalogue C1
NATURAL JOIN Articles A1
WHERE NOT EXISTS (
	SELECT * FROM Catalogue C2
	NATURAL JOIN Articles A2
	WHERE C1.fid <> C2.fid AND A1.anom = A2.anom)
	-- group by
SELECT A1.anom FROM Catalogue C1
NATURAL JOIN Articles A1
GROUP BY A1.anom
HAVING COUNT(C1.fid) = 1

--Q12
	-- not exists
SELECT DISTINCT(A1.anom) FROM Catalogue C1
NATURAL JOIN Articles A1
WHERE NOT EXISTS (
	SELECT * FROM Catalogue C2
	WHERE C2.prix <= 100 AND C1.aid=C2.aid)
	-- all
SELECT DISTINCT(A1.anom) FROM Catalogue C1
NATURAL JOIN Articles A1
WHERE C1.prix > ALL (
	SELECT C2.prix FROM Catalogue C2 
	WHERE C2.prix<=100)

--Q13
	-- exists
SELECT DISTINCT(C1.aid) FROM Catalogue C1
WHERE EXISTS (
	SELECT * FROM Fournisseurs F1
	WHERE C1.fid=F1.fid AND F1.fad LIKE '%USA')
	--not exists
SELECT DISTINCT(C1.aid) FROM Catalogue C1
WHERE NOT EXISTS (
	SELECT * FROM Fournisseurs F1
	WHERE C1.fid=F1.fid AND F1.fad NOT LIKE '%USA')
	
--Q14
SELECT F1.* FROM Fournisseurs F1
NATURAL JOIN Articles A1 NATURAL JOIN Catalogue C1
WHERE A1.acoul = 'rouge' AND NOT EXISTS (
	SELECT C2.fid FROM Catalogue C2 
	NATURAL JOIN Articles A2
	WHERE C1.fid = C2.fid AND A2.acoul <> 'rouge');

	
--Q15
SELECT F.* FROM Fournisseurs F
WHERE NOT EXISTS(
	SELECT * FROM Articles A
	WHERE A.acoul='rouge' AND NOT EXISTS(
		SELECT * FROM Catalogue C
		WHERE C.fid = F.fid AND C.aid = A.aid))
