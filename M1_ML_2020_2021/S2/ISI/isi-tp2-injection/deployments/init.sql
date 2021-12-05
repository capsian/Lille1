CREATE DATABASE IF NOT EXISTS isitp;
USE isitp;
CREATE TABLE chaines (
	id int NOT NULL AUTO_INCREMENT, 
	txt varchar(255) not null, 
	who varchar(255) not null,
	PRIMARY KEY(id)
);

CREATE TABLE chaines2 (
	id int NOT NULL AUTO_INCREMENT, 
	txt varchar(255) not null, 
	who varchar(255) not null,
	PRIMARY KEY(id)
);
INSERT INTO chaines2 (txt,who) VALUES ('findme', '0.0.0.0.0');
