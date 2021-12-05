-- doc modules stockés : https://www.postgresql.org/docs/11/plpgsql.html


create schema if not exists banque;
set search_path to banque ;

create table banque.agence(
  nag integer constraint agence_pkey primary key,
  nomag varchar(70) not null,
  villeag varchar(30)
);


INSERT INTO banque.agence VALUES (2, 'E. Zola', 'Lille');
INSERT INTO banque.agence VALUES (1, 'J. Guesdes', 'Lille');
INSERT INTO banque.agence VALUES (3, 'C. Corot', 'Lens');


create table banque.client(
  ncli integer constraint client_pkey primary key,
  nomcli varchar(30) not null,
  prenomcli varchar(30) not null,
  villecli varchar(30)
);

INSERT INTO banque.client VALUES (10, 'Lagaffe', 'Gaston', 'Villeneuve d''''Ascq');
INSERT INTO banque.client VALUES (11, 'Tournesol', 'Tryphon', 'Lille');
INSERT INTO banque.client VALUES (12, 'Tsuno', 'Yoko', 'Lille');
INSERT INTO banque.client VALUES (13, 'Cru', 'Carmen', 'Lens');
INSERT INTO banque.client VALUES (14, 'Ackerman', 'Mikasa', 'Vimy');

create table banque.compte(
  ncompte integer constraint compte_pkey primary key,
  nag integer references agence,
  solde float default 0.0 not null,
  typecpte varchar(15)
);

INSERT INTO banque.compte VALUES (145, 1, 1020, 'cpte courant');
INSERT INTO banque.compte VALUES (176, 1, 500, 'livret A');
INSERT INTO banque.compte VALUES (978, 2, 1500, 'cpte courant');
INSERT INTO banque.compte VALUES (302, 1, 100, 'cpte courant');
INSERT INTO banque.compte VALUES (529, 3, 1000, 'Ass. Vie');


create table banque.compte_client(
  ncompte integer references compte,
  ncli integer references client,
  constraint compte_client_pkey primary key(ncompte, ncli)
);

INSERT INTO banque.compte_client VALUES (145, 10);
INSERT INTO banque.compte_client VALUES (176, 10);
INSERT INTO banque.compte_client VALUES (978, 12);
INSERT INTO banque.compte_client VALUES (978, 11);
INSERT INTO banque.compte_client VALUES (302, 12);
INSERT INTO banque.compte_client VALUES (529, 14);

create table banque.emprunt(
  nemprunt integer constraint emprunt_pkey primary key,
  ncompte integer not null references compte,
  montant float not null
);

INSERT INTO banque.emprunt VALUES (1, 978, 1000);
INSERT INTO banque.emprunt VALUES (2, 145, 1500);
INSERT INTO banque.emprunt VALUES (3, 978, 2000);
INSERT INTO banque.emprunt VALUES (4, 302, 4200);


-- question 1.1 affichage des emprunts
--------------------------------------
-- première version avec une procédure (pas demandée dans le sujet)
/*
select nemprunt, ncompte, montant, nag
              from emprunt join compte_client using(ncompte)
              join compte using(ncompte) where ncli=10;
 nemprunt | ncompte | montant | nag
----------+---------+---------+-----
        2 |     145 |    1500 |   1
(1 row)
*/

create or replace procedure empruntsClient(IN idcli integer)
AS $$
DECLARE
  le_nom client.nomcli%type;
  le_prenom client.prenomcli%type;
  e record;
BEGIN
    select nomcli, prenomcli into le_nom, le_prenom from client
    where ncli = idcli ;
    raise notice 'client %', le_nom||' '||le_prenom ; -- plutôt à mettre après le if
    if not found then
      raise exception 'le client d'' identifiant % n''existe pas',idcli ;
    end if ;
    for e in select nemprunt, ncompte, montant, nag
              from emprunt join compte_client using(ncompte)
              join compte using(ncompte) where ncli=idcli loop
        --raise notice 'emprunt numero '||e.nemprunt||'de '||e.montant||'€ sur le compte '||e.ncompte||' de l''agence '||e.nag ;
        raise notice 'emprunt numero % de % € sur le compte % de l''agence %',e.nemprunt, e.montant, e.ncompte, e.nag ;
    end loop ;
    if not found then -- ou bien: if e is null then
      raise notice 'pas d''emprunt';
    end if;
END;
$$
LANGUAGE plpgsql ;

/* client avec emprunt(s)
caronc=> call empruntsClient(10);
NOTICE:  client Lagaffe Gaston
NOTICE:  emprunt numero 2 de 1500 € sur le compte 145 de l'agence 1

caronc=> call empruntsclient(12);
NOTICE:  client Tsuno Yoko
NOTICE:  emprunt numero 1 de 1000 € sur le compte 978 de l'agence 2
NOTICE:  emprunt numero 3 de 2000 € sur le compte 978 de l'agence 2
NOTICE:  emprunt numero 4 de 4200 € sur le compte 302 de l'agence 1
*/

/* client qui existe mais pas d'emprunt:
caronc=> call empruntsclient(14);
NOTICE:  client Ackerman Mikasa
NOTICE:  pas d'emprunt
*/

/* client qui n'existe pas
caronc=> call empruntsClient(1);
NOTICE:  client <NULL>
ERREUR:  le client d' identifiant 1 n'existe pas
CONTEXT:  fonction PL/pgsql empruntsclient(integer), ligne 11 à RAISE
*/

drop procedure empruntsclient ;

-- seconde version avec une fonction
create or replace function empruntsClient(idcli integer)
returns BOOLEAN
AS $$
DECLARE
  le_nom client.nomcli%type;
  le_prenom client.prenomcli%type;
  e record;
BEGIN
    select nomcli, prenomcli into le_nom, le_prenom from client
    where ncli = idcli ;
    raise notice 'client %', le_nom||' '||le_prenom ;
    if not found then
      return false ;
    end if ;
    for e in select nemprunt, ncompte, montant, nag
              from emprunt join compte_client using(ncompte)
              join compte using(ncompte) where ncli=idcli loop
        raise notice 'emprunt numero % de % € sur le compte % de l''agence %',e.nemprunt, e.montant, e.ncompte, e.nag ;
    end loop ;
    if not found then -- ou bien: if e is null then
      raise notice 'pas d''emprunt';
    end if;
    return true;
END;
$$
LANGUAGE plpgsql ;
/*
caronc=> select empruntsclient(10);
NOTICE:  client Lagaffe Gaston
NOTICE:  emprunt numero 2 de 1500 € sur le compte 145 de l'agence 1
 empruntsclient
----------------
 t
(1 row)

caronc=> select empruntsclient(12);
NOTICE:  client Tsuno Yoko
NOTICE:  emprunt numero 1 de 1000 € sur le compte 978 de l'agence 2
NOTICE:  emprunt numero 3 de 2000 € sur le compte 978 de l'agence 2
NOTICE:  emprunt numero 4 de 4200 € sur le compte 302 de l'agence 1
 empruntsclient
----------------
 t
(1 row)

caronc=> select empruntsclient(14);
NOTICE:  client Ackerman Mikasa
NOTICE:  pas d'emprunt
 empruntsclient
----------------
 t
(1 row)

caronc=> select empruntsclient(1);
NOTICE:  client <NULL>
 empruntsclient
----------------
 f
(1 row)
*/

-- question 1.2 : vérification du type de compte
------------------------------------------------
CREATE or REPLACE FUNCTION verif_compte() RETURNS trigger AS $$
    DECLARE
      t compte.typecpte%type;
      cl compte_client.ncli%type;
    BEGIN
        select compte.typecpte into t
        from compte
        where ncompte = NEW.ncompte ;
        raise notice 'type de ce compte : %',t ;
        if t != 'cpte courant' then
          select ncli into cl from compte_client
          where ncompte = NEW.ncompte;
          if found then
            raise Exception 'ce compte ne peut être partagé';
            --> on arrête là
          end if ;
        end if ;
        RETURN NEW;
    END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trig_verif_compte BEFORE INSERT OR UPDATE ON compte_client
FOR EACH ROW EXECUTE FUNCTION verif_compte();
-- attention, dans la version 10, c'était FOR EACH ROW EXECUTE PROCEDURE verif_compte() !

/*
caronc=> update compte_client set ncompte=145 where ncompte=529 and ncli=14;
NOTICE:  type de ce compte : cpte courant
UPDATE 1

caronc=> update compte_client set ncompte=176 where ncompte=145 and ncli=14;
NOTICE:  type de ce compte : livret A
ERREUR:  ce compte ne peut être partagé
CONTEXT:  fonction PL/pgsql verif_compte(), ligne 14 à RAISE

caronc=> update compte_client set ncompte=529 where ncompte=145 and ncli=14;
NOTICE:  type de ce compte : Ass. Vie
UPDATE 1

caronc=> insert into compte_client(ncompte,ncli) values (529,13);
NOTICE:  type de ce compte : Ass. Vie
ERREUR:  ce compte ne peut être partagé
CONTEXT:  fonction PL/pgsql verif_compte(), ligne 14 à RAISE

caronc=> insert into compte_client(ncompte,ncli) values (302,13);
NOTICE:  type de ce compte : cpte courant
INSERT 0 1
*/

/*
select sum(montant), solde
        from emprunt
          join compte using (ncompte)
        where ncompte = 978
        group by ncompte, solde;

 sum  | solde
------+-------
 3000 |  1500

*/

-- question 1.3 : vérification de l'endettement
-----------------------------------------------
-- dans le sujet on ne montre que des insertions,
-- je l'ai fait aussi pour des update (un delete ne va jamais violer la contrainte)
CREATE or REPLACE FUNCTION verif_endettement() RETURNS trigger AS $$
    DECLARE
      solde_cpte compte.solde%type;
      total integer;
      nouveau_montant integer ;
    BEGIN
        select sum(montant), solde into total, solde_cpte
        from emprunt
          join compte using (ncompte)
        where ncompte = NEW.ncompte
        group by ncompte, solde;
        -- un update avec modification de ncompte est à traiter comme une insertion
        if (TG_OP = 'INSERT' or OLD.ncompte <> NEW.ncompte) then
          nouveau_montant = total+NEW.montant ;
        else nouveau_montant = total+NEW.montant-OLD.montant ; -- update du montant sur le même compte
        end if ;
        raise notice 'montant total avant cet emprunt : % ; et après : % ',total,nouveau_montant;
        if (nouveau_montant > 3*solde_cpte) then
          raise exception 'limite d''emprunt atteinte';
        end if;
        RETURN NEW;
    END;
$$ LANGUAGE plpgsql;

-- drop trigger verif_endettement on emprunt;
CREATE TRIGGER verif_endettement BEFORE INSERT or UPDATE of ncompte,montant ON emprunt
    FOR EACH ROW EXECUTE FUNCTION verif_endettement();
-- si AFTER, il compte aussi le nouvel emprunt dans le select, donc il faut modifier le code
-- Quand c'est possible, préférer un trigger BEFORE, c'est moins coûteux au niveau transactionnel (coût du rollback)

/*
caronc=> insert into emprunt(nemprunt, ncompte, montant) values (11, 978, 1000);
NOTICE:  montant total avant cet emprunt : 3000 ; et après : 4000
INSERT 0 1
caronc=> select * from compte where ncompte=978;
 ncompte | nag | solde |  typecpte
---------+-----+-------+-------------
     978 |   2 |  1500 | cpte courant
(1 row)


caronc=> insert into emprunt(nemprunt, ncompte, montant) values (12, 978, 1000);
NOTICE:  montant total avant cet emprunt : 4000 ; et après : 5000
ERREUR:  limite d'emprunt atteinte
CONTEXT:  fonction PL/pgsql verif_endettement(), ligne 13 à RAISE

update emprunt set montant=500 where nemprunt=4;
ERREUR:  limite d'emprunt atteinte
CONTEXT:  fonction PL/pgsql verif_endettement(), ligne 18 à RAISE
-- normal, le solde est à 100
-- cette ligne ne respectait pas la contrainte

update emprunt set montant=200 where nemprunt=4;
NOTICE:  montant total avant cet emprunt : 4200 ; et après : 200
UPDATE 1

update emprunt set montant=2000 where nemprunt=1;
NOTICE:  montant total avant cet emprunt : 4000 ; et après : 5000
ERREUR:  limite d'emprunt atteinte
CONTEXT:  fonction PL/pgsql verif_endettement(), ligne 18 à RAISE

*/

-- question 1.4
---------------
-- le schéma définit dans COMPTE la colonne : nag integer references agence
-- Comme une clé étrangère peut être NULL, un compte peut être géré par aucune agence
-- il faut simplement rajouter un NOT NULL
Alter table Compte alter column nag set not null;

-- question 1.5
---------------
-- ici c'est plus délicat parce qu'il faut qu'il y ait toujours au moins une ligne dans la table compte_client
-- ça veut dire que la création d'un compte doit se faire avec la création d'une ligne de compte_client
create or replace function nouveauCompte(numcpte compte.ncompte%type,
                                         idag agence.nag%type,
                                         idcli client.ncli%type,
                                         libtypecpte compte.typecpte%type,
                                         soldeinitial compte.solde%type)
returns BOOLEAN
AS $$
BEGIN
    insert into Compte(ncompte, nag, solde, typecpte) values (numcpte, idag, soldeinitial, libtypecpte);
    insert into Compte_Client(ncli, ncompte) values (idcli, numcpte);
    -- grâce aux contraintes d'intégrité référentielles, si le client n'existe pas ou si l'agence n'existe pas
    -- on quitte la fonction avec une exception
    -- Ici, le return ne sert à rien (on a plutôt affaire à une procédure.)
    return true;
END;
$$
LANGUAGE plpgsql ;

/*
=> select nouveauCompte(24,1,12,'livret A',0.0);
NOTICE:  type de ce compte : livret A
 nouveaucompte
---------------
 t
(1 row)
--> Les 2 lignes sont bien insérées dans Compte et Compte_Client

-- on essaie avec un client qui n'existe pas
=> select nouveauCompte(25,1,20,'livret A',0.0);
ERREUR:  une instruction insert ou update sur la table « compte_client » viole la contrainte de clé
étrangère « compte_client_ncli_fkey »
DETAIL:  La clé (ncli)=(20) n'est pas présente dans la table « client ».
--> aucune ligne n'est insérée.

-- idem si on passe une agence qui n'existe pas
=> select nouveauCompte(25,5,11,'livret A',0.0);
ERREUR:  une instruction insert ou update sur la table « compte » viole la contrainte de clé
étrangère « compte_nag_fkey »
DETAIL:  La clé (nag)=(5) n'est pas présente dans la table « agence ».
*/

-- il faudrait aussi s'assurer qu'un update de compte_client ne rend pas un compte "orphelin"
-- Il peut être logique d'interdire les update sur cette table compte_client
--> utiliser les droits plutôt qu'une solution procédurale.

-- passer par une fonction aussi pour vérifier la suppression sur compte_client
create or replace function supprimerProprioCompte(numcpte compte.ncompte%type,
                                         idcli client.ncli%type)
returns BOOLEAN
AS $$
DECLARE
  nb integer;
BEGIN
    select count(*) into nb
    from compte_client
    where ncompte = numcpte ;
    if nb > 1 then
      delete from compte_client where ncompte = numcpte and ncli = idcli ;
    else
      raise Exception 'un compte doit avoir au moins 1 propriétaire';
    end if ;
    return true;
END;
$$
LANGUAGE plpgsql ;

/*
select supprimerProprioCompte(978, 12);
--> ok

select supprimerProprioCompte(176, 10);
ERREUR:  un compte doit avoir au moins 1 propriétaire
CONTEXT:  fonction PL/pgsql supprimerpropriocompte(integer,integer), ligne 11 à RAISE
*/

-- De plus, on peut ajouter la contrainte "on delete cascade" sur la clé étrangère entre compte_client et compte
--> la suppression d'un compte entraine la suppression de toutes les lignes de compte_client qui concernent ce compte
-- \d compte_client permet de voir les contraintes présentes sur la table

-- on supprime l'ancienne contrainte
alter table compte_client drop constraint compte_client_ncompte_fkey;

-- on définit la nouvelle
Alter table Compte_client add foreign key(ncompte) references compte on delete cascade;

/*
\d compte_client
            Table "banque.compte_client"
 Column  |  Type   | Collation | Nullable | Default
---------+---------+-----------+----------+---------
 ncompte | integer |           | not null |
 ncli    | integer |           | not null |
Indexes:
    "compte_client_pkey" PRIMARY KEY, btree (ncompte, ncli)
Foreign-key constraints:
    "compte_client_ncli_fkey" FOREIGN KEY (ncli) REFERENCES client(ncli)
    "compte_client_ncompte_fkey" FOREIGN KEY (ncompte) REFERENCES compte(ncompte) ON DELETE CASCADE
Triggers:
    trig_verif_compte BEFORE INSERT OR UPDATE ON compte_client FOR EACH ROW EXECUTE PROCEDURE verif_compte()

*/
