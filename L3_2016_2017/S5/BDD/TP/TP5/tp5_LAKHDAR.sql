--Q1
SELECT C.eid, MAX(A.portee) FROM Certifications C
NATURAL JOIN Avions A
GROUP BY C.eid
HAVING COUNT(C.aid)>=2
	
--Q2
SELECT E1.enom FROM Employes E1
WHERE EXISTS (
	SELECT * FROM Vols
	WHERE dep='CDG' AND arr='NOU' AND E1.salaire < prix)
	
--Q3
SELECT * FROM Vols V
WHERE EXISTS (
	SELECT * FROM Employes E
	NATURAL JOIN Certifications C NATURAL JOIN Avions A
	WHERE E.salaire > 100000 AND A.portee >= V.distance)
	
--Q4
-- not exists
SELECT DISTINCT(E.enom) FROM Employes E
NATURAL JOIN Certifications C NATURAL JOIN Avions A
WHERE A.portee > 1500 AND NOT EXISTS (
	SELECT * FROM Employes E2
	NATURAL JOIN Certifications C2 NATURAL JOIN Avions A2
	WHERE E2.eid = E.eid AND A2.portee < 1500)
-- every
SELECT E.enom FROM Employes E
NATURAL JOIN Certifications C NATURAL JOIN Avions A
GROUP BY E.enom
HAVING EVERY(A.portee>1500)
	
--Q5
SELECT E.enom FROM Employes E
NATURAL JOIN Certifications C NATURAL JOIN Avions A
GROUP BY E.enom
HAVING COUNT(C.aid) > 1 AND EVERY(A.portee > 1500)

--Q6
SELECT E.enom FROM Employes E
NATURAL JOIN Certifications C NATURAL JOIN Avions A
GROUP BY E.enom
HAVING bool_or(A.anom LIKE '%Boeing%') AND EVERY(A.portee > 1500)

--Q7 [ TODO:meilleur version ? ]
SELECT E0.eid FROM Employes E0
	WHERE E0.salaire = ( 
	SELECT MAX(E.salaire) FROM Employes E
	WHERE E.eid <> SOME (
		SELECT E2.eid FROM Employes E2
		WHERE E.salaire<E2.salaire ))

--Q8
SELECT DISTINCT E.enom FROM Employes E
NATURAL JOIN Certifications C NATURAL JOIN Avions A
GROUP BY E.eid
HAVING bool_or(A.portee > 2000) AND EVERY(A.anom NOT LIKE '%Boeing%')

--Q9
SELECT E.enom FROM Employes E
WHERE E.eid NOT IN (
	SELECT C.eid FROM Certifications)
GROUP BY E.eid
HAVING E.salaire > AVG(E.salaire)
	
--Q10
-- Vue revenue moyen des pilotes
CREATE VIEW V_RevenueM_Pilote AS
SELECT AVG(E.salaire) FROM Employes E
NATURAL JOIN Certifications C
-- Vue revenue moyen des non pilotes
CREATE VIEW V_RevenueM_Employes AS
SELECT AVG(E.salaire) FROM Employes E

SELECT ( SELECT * FROM V_RevenueM_Pilote) - ( SELECT * FROM V_RevenueM_Employes) AS diff

--Q11
SELECT * FROM Vols V
WHERE V.dep = 'Madison' AND EXISTS (
	SELECT * FROM Vols V2
	WHERE V2.arr ='New York' 
	AND (EXTRACT(HOUR FROM V2.h_dep) > EXTRACT(HOUR FROM V.h_arr) OR (EXTRACT(HOUR FROM V.h_arr) <= 18 AND V.arr ='New York'))
	AND EXTRACT(HOUR FROM V2.h_arr) <= 18)


--Q12 [correct ?]
SELECT * FROM Vols V
WHERE V.dep = 'La Tantouta' AND EXISTS (
	SELECT * FROM Vols V2
	WHERE V2.dep = V.arr 
	AND EXTRACT(HOUR FROM V2.h_dep) > EXTRACT(HOUR FROM V.h_arr) 
	AND V.vid <> V2.vid
	AND EXISTS(
		SELECT * FROM Vols V3
		WHERE V3.arr='Timbuktu'
		AND EXTRACT(HOUR FROM V3.h_dep) > EXTRACT(HOUR FROM V2.h_arr)
		AND V2.vid <> V3.vid AND V.vid <> V3.vid))
