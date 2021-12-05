CREATE OR REPLACE FUNCTION empruntsclient (client_id banque.client.ncli%type)
RETURNS boolean AS $ok$
declare
	prenom varchar(30);
	nagence integer;
	ok boolean;
	empr record;
	client_cmpt_id integer;
BEGIN
   SELECT prenomcli INTO prenom FROM banque.client WHERE ncli = client_id;
   IF NOT FOUND THEN
   	ok = FALSE;
   else
	ok = TRUE;
   	raise notice 'Client : %', prenom;
   	
   	-- get compte_id
   	SELECT ncompte INTO client_cmpt_id FROM banque.compte_client WHERE ncli = client_id;
   	-- get agence
   	SELECT nag INTO nagence FROM banque.compte WHERE ncompte = ncompte;
   	
   	FOR empr IN (SELECT * FROM banque.emprunt WHERE ncompte = client_cmpt_id) LOOP
   		raise notice 'emprunt numero : % de % € sur le compte % de l agence %', empr.nemprunt, empr.montant, empr.ncompte, nagence;
   	END LOOP;
   end if;
   RETURN ok;
END;
$ok$ LANGUAGE plpgsql;


-- V2
CREATE OR REPLACE FUNCTION empruntsclient (client_id banque.client.ncli%type)
RETURNS boolean AS $ok$
declare
    prenom varchar(30);
    nagence integer;
    ok boolean;
    empr record;
    cli_emp_id integer;
    client_cmpt_id integer;
BEGIN
   SELECT prenomcli INTO prenom FROM banque.client WHERE ncli = client_id;
   IF NOT FOUND THEN
       ok = FALSE;
   else
    	ok = TRUE;
       	raise notice 'Client : %', prenom;

       -- get compte_id
       FOR cli_emp_id in (SELECT ncompte  FROM banque.compte_client WHERE ncli = client_id) LOOP
         -- get agence
         SELECT nag INTO nagence FROM banque.compte WHERE cli_emp_id = ncompte;

         FOR empr IN (SELECT * FROM banque.emprunt WHERE ncompte = cli_emp_id) LOOP
             raise notice 'emprunt numero : % de % € sur le compte % de l agence %', empr.nemprunt, empr.montant, empr.ncompte, nagence;
         END LOOP;
        END LOOP;
   end if;
   RETURN ok;
END;
$ok$ LANGUAGE plpgsql;


-- q2
CREATE FUNCTION compte_type_trigger() returns trigger as $$
declare
    cmpt record;
    cmp_typ integer;
BEGIN
	-- get compte type
    SELECT typecpte INTO cmp_typ FROM banque.compte WHERE ncompte = new.ncompte
    IF NOT FOUND THEN
    	-- all right !
    	RETURN new;
    END IF;
    raise notice 'type de compte %', cmp_typ;
    
    FOR cmpt IN (SELECT * FROM banque.compte) LOOP
    	
        -- check no dup
        IF cmpt.ncompte == new.ncompte THEN
        	
        END IF;

       END LOOP;
    RETURN new;
END
$$ LANGUAGE plpgsql;

CREATE TRIGGER compte_client_trigg
BEFORE update OR insert ON compte_client 
FOR EACH ROW 
EXECUTE FUNCTION compte_type_trigger() ;
