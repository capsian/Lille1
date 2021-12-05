--
-- 	Database Table Creation
--
DROP TABLE participer CASCADE CONSTRAINTS;

DROP TABLE cours CASCADE CONSTRAINTS;

DROP TABLE etudiants CASCADE CONSTRAINTS;

DROP TABLE profs CASCADE CONSTRAINTS;

---

CREATE TABLE etudiants(
	e_id int primary key,
	e_nom varchar(30),
	programme varchar(25),
	niveau varchar(10),--
	age int
	);

CREATE TABLE profs(
prof_id int primary key,
	prof_nom varchar(30),
	lab_id int
	);

CREATE TABLE cours(
       c_id int primary key,
       	titre varchar(40) unique, 
	horaire varchar(20),
	salle varchar(10),
	prof_id int,
    foreign key(prof_id) references profs
	);

CREATE TABLE participer(
	e_id int,
	c_id int,
	primary key(e_id,c_id),
	foreign key(e_id) references etudiants,
	foreign key(c_id) references cours(c_id)
	);

---------
