# Q8
Lisez le fichier microblog.sql et expliquez brièvement les différentes fonctionnalité de cette base de données.

- Table user_store
	- index sur le champ name
	- fonction create_user
		- génère un mdp chiffré avec salt grâce à la fonction gen_salt
		- retourne le user_id
- Table messages_store
	- index sur published_date
	- CLUSTER (Voir plus bas)
	- fonction insert_message
		- insert message en demandant le mdp
	- view messages
 		- jointure avec user_store
		- order desc
Table followers
	- correspondance
	- index sur user_source, user_target
	- fonction feed
		- retourne le feed d'un user
	- fonction follow
		- follow une personne
- Roles
	- common_user
		- LOGIN
		- EXEC func 
			- create_user
			- insert_message
			- follow
			- feed
		- SELECT on messages
		
# Q9: 
- Est-ce qu’il est possible pour l’utilisateur common_user:
    - de récupérer la totalité des messages publiés:
    	- Oui
    - de récupérer la liste des utilisateurs inscrits:
    	- Oui
    - de récupérer le mot de passe d’un utilisateur inscrit:
    	- Non
- Est-il possible pour l’utilisateur possédant la base de données:
    - de récupérer la totalité des messages publiés:
    	- Oui
    - de récupérer la liste des utilisateurs inscrits:
    	- Oui
    - de récupérer le mot de passe d’un utilisateur inscrit
    	- Oui mais pas en clair.

# Q10: 
A quoi sert la ligne: `CLUSTER messages_store USING idx_pub_date;`
- https://www.postgresql.org/docs/current/sql-cluster.html
```
CLUSTER instructs PostgreSQL to cluster the table specified by table_name based on the index specified by index_name. The index must already have been defined on table_name.
	
When a table is clustered, it is physically reordered based on the index information. Clustering is a one-time operation: when the table is subsequently updated, the changes are not clustered. That is, no attempt is made to store new or updated rows according to their index order. (If one wishes, one can periodically recluster by issuing the command again. Also, setting the table's fillfactor storage parameter to less than 100% can aid in preserving cluster ordering during updates, since updated rows are kept on the same page if enough space is available there.)

When a table is clustered, PostgreSQL remembers which index it was clustered by. The form CLUSTER table_name reclusters the table using the same index as before. You can also use the CLUSTER or SET WITHOUT CLUSTER forms of ALTER TABLE to set the index to be used for future cluster operations, or to clear any previous setting.

CLUSTER without any parameter reclusters all the previously-clustered tables in the current database that the calling user owns, or all such tables if called by a superuser. This form of CLUSTER cannot be executed inside a transaction block.

When a table is being clustered, an ACCESS EXCLUSIVE lock is acquired on it. This prevents any other database operations (both reads and writes) from operating on the table until the CLUSTER is finished
```
- https://www.educba.com/postgresql-cluster
```
Clustering highly increases the performance and retrieves the query resultset very quickly as the execution, i.e. lowers done because the records are now present in the single location after clustering and are not in the distorted format. This gradually affects the availability of the database for users. As execution time decreases, the access time decreases, making the database available for other users, thus achieving high performance and database availability.
```

# Q11:
```
CREATE OR REPLACE FUNCTION get_user_messages(TEXT) RETURNS json AS -- username
$BODY$
DECLARE
    found_uuid TEXT;
BEGIN
    -- retrieve uuid
    SELECT user_id INTO found_uuid FROM user_store WHERE name = $1;
    -- Build the JSON Response:
    RETURN (
        SELECT json_build_object(
                       'user_id', (found_uuid),
                       'messages', (SELECT json_agg(content) FROM messages_store WHERE user_id = uuid(found_uuid) LIMIT 10)
                   )
    );
END
$BODY$
LANGUAGE 'plpgsql';
```

# Q12:
- /etc/postgresql/13/main/pg_hba.conf
```
host    all             common_user		0.0.0.0/0		trust
```
```
$ psql -h 172.28.100.140 -U common_user microblog
psql (12.8 (Ubuntu 12.8-0ubuntu0.20.04.1), server 13.4 (Ubuntu 13.4-1.pgdg20.04+1))
WARNING: psql major version 12, server major version 13.
         Some psql features might not work.
SSL connection (protocol: TLSv1.3, cipher: TLS_AES_256_GCM_SHA384, bits: 256, compression: off)
Type "help" for help.
microblog=> \q
```
