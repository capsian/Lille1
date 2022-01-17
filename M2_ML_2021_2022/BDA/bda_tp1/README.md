# BDA TP1
## https://www.paperman.name/page/enseignement/2021/nosql/TD1.html

# Author
- Selim Lakhdar
	- selim.lakhdar.etu@univ-lille.fr
	- selim.lakhdar@gmail.com
	
# VMs
- bda-1 : 172.28.100.140
- bda-2 : 172.28.100.203
- bda-3 : 172.28.100.75
- bda-4 : 172.28.100.172	

# Questions
- Voir fichier reponses.md

# Setup
```
# Init users & passwords & install postgres & set firewall rules
./scripts/setup.sh
# Create db users, set permissions & import db
./scripts/postgresql.sh
# Generate users for microblog app
./scripts/users_generation.sh
```

# Remote login
```
lakhdar@a11p26:~$ psql -h 172.28.100.140 -U ubuntu -d microblog
Password for user ubuntu: 
psql (12.8 (Ubuntu 12.8-0ubuntu0.20.04.1), server 13.4 (Ubuntu 13.4-1.pgdg20.04+1))
WARNING: psql major version 12, server major version 13.
         Some psql features might not work.
SSL connection (protocol: TLSv1.3, cipher: TLS_AES_256_GCM_SHA384, bits: 256, compression: off)
Type "help" for help.

microblog=# \q
```

# Benchmarking
```bash
# on vm1
ubuntu@bda-1:~$ pg_activity -U ubuntu -h 172.28.100.140 -d microblog --output=pg_activity.log
# on fil workstation
./scripts/users_insert.sh
```
- On remarque que le TPS augmente de 5/7 à 50/60/67

```bash
# on vm1
ubuntu@bda-1:~$ pg_activity -U ubuntu -h 172.28.100.140 -d microblog --output=pg_activity.log
# on fil workstation
python3 ./benchmarking/say_hello.py
```
- On remarque que le TPS varie jusqu'à 50.

```bash
# on vm1
ubuntu@bda-1:~$ pg_activity -U ubuntu -h 172.28.100.140 -d microblog --output=pg_activity.log 
# on fil workstation
python3 ./benchmarking/say_hello.py
python3 ./benchmarking/say_hello.py
python3 ./benchmarking/say_hello.py
python3 ./benchmarking/say_hello.py
```
- On remarque que le max de TPS est de ~150
- On remarque que le acc_time est plus élevé (augmente plus vite)
  - Les requetes prennent plus de temps à etre executé

# Publication/Subscription
```bash
# on vm1
ubuntu@bda-1:~/bda_tp1$ ./scripts/postgresql_publication.sh
# on vm2
ubuntu@bda-2:~/bda_tp1$ ./scripts/postgresql_subscription.sh 
```

- On remarque que les données sont répliquées sur la deuxième BDD.
- La solution se situe entre Consistency qui impose la cohérence et Partition Tolerance.
