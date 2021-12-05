drop table TP5;

create table TP5(
    A int,
    B int
);

insert into TP5 values (0,0); -- init
insert into TP5 values (2,3); -- init
insert into TP5 values (0,1); -- init

-- Q1.1
    BEGIN;
    insert into TP5 values (4,4);
    insert into TP5 values ('a', 'b'); -- ERREUR:  la transaction est annulée, les commandes sont ignorées jusqu'à la fin du bloc
    select * from TP5;
    COMMIT;

    BEGIN;
    insert into TP5 values (5,5);
    insert into TP5 values (6,6);
    select * from TP5;
    ROLLBACK;
    select * from TP5;
    COMMIT;
    -- On n'écrit rien à la fin

-- Q1.2
    -- T1
    BEGIN;
        UPDATE TP5 SET A = A+1;
        -- T2
        select * from TP5;
        -- T2
        select * from TP5;
    COMMIT;

    -- T2
    BEGIN;
        --
        UPDATE TP5 SET A = A+1;
        --
    COMMIT;
    -- On remarque que T1 ne remarque pas le update tant qu'il n'est pas commit

-- Q1.3
    -- T1
    BEGIN;
        UPDATE TP5 SET A = A+1;
        select * from TP5;
        -- T2
        -- T2
        -- T2
        -- T2
    COMMIT;

    -- T2
    BEGIN;
        -- T1
        -- T1
        insert into TP5 values (3,7);
        select * from TP5;
        DELETE FROM TP5 WHERE A = 2;  -- Bloquant !
        DELETE FROM TP5 WHERE A = 1;  
        --
    COMMIT;
    -- N'est pas seriable.
    
    
-- Q1.4
    -- T1
    BEGIN;
        UPDATE TP5 SET A = 3 where A = 2; -- Verrou sur ligne A
        -- T2
        -- T2
        select * from TP5;
        -- T2
        UPDATE TP5 SET B = 2 where B = 3; -- Bloquant !
    COMMIT;

    -- T2
    BEGIN;
        -- T1
        UPDATE TP5 SET B = 2 where B = 3; -- Verrou sur ligne B
        select * from TP5;
        -- T1
        UPDATE TP5 SET A = 3 where A = 2; -- Bloquant
        -- T1
    COMMIT;
    -- Les verrous sont posés sur A et B.
    -- L'une des deux sessions va écouher.
    
-- Q1.5
    -- T1
    BEGIN;
        select * from TP5 where B = 7 for update;
        -- T2
        -- T2
        -- T2
        UPDATE TP5 SET B = 6 where B = 7;
    COMMIT;

    -- T2
    BEGIN;
        -- T1
        UPDATE TP5 SET B = 10 where B = 0; -- Non Bloquant
        select * from TP5;
        UPDATE TP5 SET A = 5 where A = 3; -- Bloquant
        -- T1
        -- T1
        -- T1
    COMMIT;
    select * from TP5;
    -- Verrou sur colonne A
    
    
    
    
    
    
    
    
    