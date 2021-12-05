--
---------------------------------------------------------------------------


drop table if exists skippers cascade;
drop table if exists bateaux cascade;
drop table if exists reservations cascade;


-- creations

create table skippers(
        sid integer,
        snom varchar(30),
        niveau integer,
        age integer,
        primary key(sid)
        );

create table bateaux(
        bid integer,
        bnom varchar(30),
        couleur varchar(10),
        primary key(bid)
        );

create table reservations(
        sid integer,
        bid integer,
        jour date,
        primary key(sid,bid,jour),
        foreign key(sid) references skippers,
        foreign key(bid) references bateaux
        );


-- inserts

insert into skippers (sid, snom, niveau, age)
        values (22, 'Dustin', 7, 45.0);
insert into skippers (sid, snom, niveau, age)
        values (29, 'Brutus', 1, 33.0);
insert into skippers (sid, snom, niveau, age)
        values (31, 'Lubber', 8, 55.5);
insert into skippers (sid, snom, niveau, age)
        values (32, 'Andy', 8, 25.5);
insert into skippers (sid, snom, niveau, age)
        values (58, 'Rusty', 10, 35.0);
insert into skippers (sid, snom, niveau, age)
        values (64, 'Horatio', 7, 35.0);
insert into skippers (sid, snom, niveau, age)
        values (71, 'Zorba', 10, 16.0);
insert into skippers (sid, snom, niveau, age)
        values (74, 'Horatio', 9, 35.0);
insert into skippers (sid, snom, niveau, age)
        values (85, 'Art', 3, 25.5);
insert into skippers (sid, snom, niveau, age)
        values (95, 'Bob', 3, 63.5);

insert into bateaux (bid, bnom, couleur)
        values (101, 'Interlake', 'blue');
insert into bateaux (bid, bnom, couleur)
        values (102, 'Interlake', 'red');
insert into bateaux (bid, bnom, couleur)
        values (103, 'Clipper', 'green');
insert into bateaux (bid, bnom, couleur)
        values (104, 'Marine', 'red');

insert into reservations (sid, bid, jour)
        values (22, 101, '10/10/12');
insert into reservations (sid, bid, jour)
        values (22, 102, '10/10/12');
insert into reservations (sid, bid, jour)
        values (22, 103, '10/8/12');
insert into reservations (sid, bid, jour)
        values (22, 104, '10/7/12');
insert into reservations (sid, bid, jour)
        values (31, 102, '11/10/12');
insert into reservations (sid, bid, jour)
        values (31, 103, '11/6/12');
insert into reservations (sid, bid, jour)
        values (31, 104, '11/12/12');
insert into reservations (sid, bid, jour)
        values (64, 101, '9/5/12');
insert into reservations (sid, bid, jour)
        values (64, 102, '9/8/12');
--insert into reservations (sid, bid, jour)
--        values (64, 102, '10/8/12');
insert into reservations (sid, bid, jour)
        values (74, 103, '9/8/12');


