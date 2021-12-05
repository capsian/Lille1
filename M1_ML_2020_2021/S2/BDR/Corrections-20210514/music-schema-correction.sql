DROP SCHEMA IF EXISTS music CASCADE;

CREATE SCHEMA IF NOT EXISTS music;
SET SCHEMA 'music';

create table album(
  al_id Numeric(4) constraint album_pkey primary key,
  al_titre Varchar(100) not null,
  al_sortie Date
);

create table produit(
  prod_id Numeric(4) constraint produit_pkey primary key,
  prod_al Numeric(4) constraint produit_album_fkey references ALBUM,
  prod_code_barre_ean Varchar(13) not null,
  prod_type_support Varchar(3) -- par exemple 'CD', 'DVD', ou 'Vi' pour vinyle
);

--
-- On modifie la table facture pour qu'elle soit découpée suivant la colonne fac_date
create table facture(
  fac_num Numeric(5),  -- on supprime la contrainte de clé primaire sur la colonne fac_num
  fac_date Date not null,
  fac_montant Numeric(6,2) default 0.0 not NULL
) PARTITION BY RANGE(fac_date);


create table ligne_facture(
  lig_produit Numeric(4) constraint ligne_produit_fkey references PRODUIT,
  lig_facture Numeric(5), -- on supprime la contrainte de clé étrangère sur ligne_facture
  lig_prix_vente Numeric(4,2) default 0.0 not null,
  lig_quantite Numeric(2) default 1 not null,
  constraint ligne_facture_pkey primary key(lig_facture, lig_produit)
);


-- question 2 et 4
CREATE OR REPLACE FUNCTION tablePartitionFactureDate(laDate DATE)
  RETURNS BOOLEAN AS $$
  DECLARE
  nom_partition TEXT;
  nom_index TEXT;
  date_debut DATE;
  date_fin DATE;
BEGIN
  nom_partition := 'facture_' || to_char(laDate, 'YYYY_MM');
  IF NOT EXISTS(SELECT relname FROM pg_class WHERE relname = nom_partition)
  THEN
    date_debut := date_trunc('month', laDate);
    date_fin := date_debut + INTERVAL '1 month';
    RAISE NOTICE 'Création de la partition % pour les dates du % à %',
      nom_partition, date_debut, date_fin;
    EXECUTE 'CREATE TABLE ' || nom_partition ||'(
                                               fac_num Numeric(5) PRIMARY KEY,
                                               fac_date Date NOT NULL,
                                               fac_montant Numeric(6,2) default 0.0 not NULL
                                               ) ';
    EXECUTE 'ALTER TABLE facture ATTACH PARTITION ' || nom_partition ||
      ' FOR VALUES FROM (''' || date_debut || ''') TO (''' || date_fin || ''')';
    nom_index := nom_partition || '_idx';
    EXECUTE 'CREATE INDEX ' || nom_index || ' ON ' || nom_partition || '(fac_date)';
    END IF;
  RETURN TRUE;
END;$$
LANGUAGE 'plpgsql';
-- question 3
CREATE OR REPLACE FUNCTION partitionFactureAnnee(laDate DATE)
  RETURNS BOOLEAN AS $$
  DECLARE
  date_mois record;
  st_date DATE;
  lst_date DATE;
BEGIN
  st_date := date_trunc('month',laDate);
  lst_date := st_date + INTERVAL '11 month';
  FOR date_mois IN SELECT generate_series AS mois FROM generate_series(st_date::DATE, lst_date::DATE, '1 month')
    LOOP
    PERFORM tablePartitionFactureDate(date_mois.mois::DATE);
  END LOOP;
  RETURN TRUE;
END;$$
LANGUAGE 'plpgsql';

SELECT partitionFactureAnnee('2020-01-01');

-- question 5

CREATE OR REPLACE FUNCTION partitionSurSixDerniersMois()
  RETURNS BOOLEAN AS $$
  DECLARE
    current_month DATE;
    six_month_ago DATE;
    nom_partition TEXT;
    tbl_part record;
    date_mois record;
  BEGIN
    current_month := date_trunc('month', NOW());
    six_month_ago := current_month - INTERVAL '5 month';
    nom_partition := 'facture_' || six_month_ago;
    FOR tbl_part IN (SELECT relname FROM pg_class WHERE relname SIMILAR TO  'facture\_[0-9]{4}\_[0-9]{2}' AND relname < nom_partition AND relispartition)
    LOOP
      RAISE NOTICE 'Détache la table % de la partition facture', tbl_part.relname;
      EXECUTE 'ALTER TABLE facture DETACH PARTITION '  || tbl_part.relname;
    END LOOP;
    FOR date_mois IN (SELECT generate_series AS mois FROM generate_series(six_month_ago::DATE, current_month::DATE, '1 month'))
    LOOP
      PERFORM tablePartitionFactureDate(date_mois.mois::DATE);
    END LOOP;
    RETURN TRUE;
  END;$$
  LANGUAGE 'plpgsql';

-- question 6
-- On peut écrire un script et l'enregistrer sur la crontab du serveur pour se déclencher chaque mois.
-- Ce script interagit avec la base de données pour
-- 1. déclencher la fonction de la question 5 et
-- 2. récupérer la liste des partitions détachée.
-- Il fait ensuite un dump pour chaque table détachée (via le shell).
-- Enfin il interagit de nouveau avec la base pour effacer les tables de la base de données.
