# TP3 NP
---------------

## Author

* Selim Lakhdar <selim.lakhdar@gmail.com> <selim.lakhdar.etu@univ-lille.fr>


#### Certificat V1

- Un tableau à 2 dim, de taille n, représantant le début de chaque tâche, ainsi que la machine qui lui est affectée.

- La taille est bien bornée polynomialement par rapport à la taille de l'entrée.

| | début | machine |
|:----: | :----: | :----: |
| t1 | 2 | 1 |
| t2 | 0 | 1 |
| t3 | 6 | 2 |
| t4 | 4 | 1 |
| t5 | 0 | 2 |


#### Algo Valid Certif V1: 
```
	entrées: cert : tableau à 2 dim, ta : tableau des tâches, D : durée d'attente max
	var : tab_machines: tableau à 2 dim ()  
	debut  
	
	  pour chaque tâches t faire  
	    d_i = cert[t][0]  
	    m_i = cert[t][1]  
	    si (d_i - ta[t] > D) || (d_i < ta[t]) alors  // ta[t] = a_i 
	      retour faux  
	    fsi  
	  fpour  
	
	  pour chaque machines m faire  
	    tab_machines[m] = récup_tt_tâches_de_M(m)  
	  fpour
	
	  pour chaque machines m  
	    trier(tab_machines[m])  // trier par d_i
	    verif(tab_machines[m]) // d_i + t_i <= d_i+1 
	  fpour  
	fin
```

==> O(nlogn)

#### Q1 - V2

- Tableau de taille n, représentant le début de chaque tâche.
    
| | début |
|:----: | :----: |
| t1 | 2 |
| t2 | 0 |
| t3 | 6 |
| t4 | 4 |
| t5 | 0 |


#### Q1 - V3

- Tableau de taille n, représentant la pos de chaque tâche:
    
| | pos |
|:----: | :----: |
| t1 | 2 |
| t2 | 0 |
| t3 | 3 |
| t4 | 4 |
| t5 | 1 |

#### Algo Valid Certif V2: 
```
# update time and return pos if a machine is available
def update_machines_exec_time(elp_time):
    pos = -1
    for t in range(len(machines_exec_time)):
        if elp_time > machines_exec_time[t]:
            pos = t
            machines_exec_time[t] = 0
        else:
            machines_exec_time[t] -= elp_time
    return pos 


def valid_certif(certif):
    # represent the remain time of task exec on each machine
    machines_exec_time = [0] * m
    last_curr_time = 0

    for _ in range(len(certif)):

        # take the task that begins the first
        task_pos = np.argmin(certif)

        # check if the task is lunched after submit time
        if certif[task_pos] < tasks[task_pos][0]:
            return False

        # check if task is lunched before max wait d
        if certif[task_pos] - tasks[task_pos][0] > d:
            return False

        curr_time = certif[task_pos]
        elapsed_time = abs(curr_time - last_curr_time)       

        # check if there is a place
        machine_pos = update_machines_exec_time(elapsed_time)
        if machine_pos != -1:
            machines_exec_time[machine_pos] = tasks[task_pos][1]  # task duration
        else:
            print("no more machines.... failed")
            return False

        last_curr_time = curr_time

        # del task
        certif[task_pos] = np.inf

    return True
```

#### Algo Valid Certif V3: 
```
# certif: [task_pos ...]
def valid_certif(certif):
    # represent the remain time of task exec on each machine
    machines_exec_time = [0] * m
    last_curr_time, curr_time = 0, 0

    # update time and return pos if a machine is available
    def update_machines_exec_time(elp_time):
        pos = -1
        for t in range(len(machines_exec_time)):
            if elp_time >= machines_exec_time[t]:
                pos = t
                machines_exec_time[t] = 0
            else:
                machines_exec_time[t] -= elp_time
        return pos

    for _ in range(len(certif)):

        # take the task that begins the first
        task_pos = int(np.argmin(certif))
        curr_time = tasks[task_pos][0]

        # check if the task is lunched after submit time
        if tasks[task_pos][0] < curr_time:
            return False

        # check if task is lunched before max wait d
        if tasks[task_pos][0] - curr_time > d:
            return False

        elapsed_time = abs(curr_time - last_curr_time)
        m_pos = update_machines_exec_time(elapsed_time)
        if m_pos == -1:
            for _ in range(0, d):
                curr_time += 1
                m_pos = update_machines_exec_time(i)
                if m_pos != -1:
                    break
            if m_pos == -1:
                print("No more machines !!!")
                return False

        machines_exec_time[m_pos] = tasks[task_pos][1]
        last_curr_time = curr_time

        # del task
        certif[task_pos] = np.inf

    return True
```


#### Q2.1 : Algo_Random_Certif

	entrées: D : durée d'attente max, M : nb de machines, ta: tableau de tâches (dates d'arrivé)
	var : res: tableau à 2 dim ()  
	debut  
	
	  pour chaque tâches t faire  
	    d_i = random(ta[t],ta[t]+D)
	    m_i = random(M)
	    
	    res[t][0] = d_i  
	    res[t][1] =  m_i
	  fpour  
	
	  retour res  
	fin
	
==> O(n)

#### Q2.2 : Algo_JSB  
    
	entrées: D : durée d'attente max, M : nb de machines, ta: tableau de tâches (dates d'arrivé)
        
    debut
    
        tq ( ! Algo_Valide_Certif( res = Algo_Random_Certif(D,M,ta))) faire
        ftq
        
        retourner res
    fin

==> NP    
    
#### Q3.1 :
  
nombre de certif = ((d+1)*nb_m)^nb_t 

#### Q3.2 : Algo_getCertif_ordre

Si on prend le certif V2, on peut imposer cette ordre:

| | début |
|:----: | :----: |
| t1 | 0 |
| t2 | 0 |
| t3 | 0 |
| t4 | 0 |
| t5 | 0 |

puis 

| | début |
|:----: | :----: |
| t1 | 0 |
| t2 | 0 |
| t3 | 0 |
| t4 | 0 |
| t5 | 1 |

...

| | début |
|:----: | :----: |
| t1 | 0 |
| t2 | 0 |
| t3 | 0 |
| t4 | 1 |
| t5 | 0 |

---------------------------------------

Si on prend le certif V3, on peut imposer cette ordre:

| | début |
|:----: | :----: |
| t1 | 0 |
| t2 | 1 |
| t3 | 2 |
| t4 | 3 |
| t5 | 4 |

puis 

| | début |
|:----: | :----: |
| t1 | 1 |
| t2 | 0 |
| t3 | 2 |
| t4 | 3 |
| t5 | 4 |

...

| | début |
|:----: | :----: |
| t1 | 4 |
| t2 | 3 |
| t3 | 2 |
| t4 | 1 |
| t5 | 0 |

   
#### Q3.2 : Algo_British_Museum

    entrée : m: nb machines, n: nb taches, D: temps attente, ta: tableau de taches, k: ordre
    var : res   : tab 2 dim [n,2]
          limit : ((d+1)*nb_m)^nb_t 
          rand  :  entier
    debut
    
        faire
       
            rand = rand() % limit
            res = Algo_getCertif_ordre(m,n,D,ta,rand)
        
        tq (Algo_Valide_Certif(res) != TRUE)
    
        retourner res
    fin
    
==> O ( INFINI )

#### Q5 : Reduction: Partition

Partition => red(I) => JSP

	Algo: red  
        entrées: tab: tableau de n entiers, d: sum(n_i)/2
        var: m : entier
            matrix: matrice d'entier de dim 2
        debut
  
            tab[n] = d // ajout de l'elem
            tab[n+1] = d // ajout de l'elem
            // init matrix
            pour i de 0 à n+2 faire
                matrix[i][0] = 0
                matrix[i][1] = tab[i]
            fpour
            
            m = 2
            JSP(m,matrix,d)
        fin


| m2 | m1 |
|:----: | :----: |
| 12 | d=16 |
| 4  | - |
| 7  | d=16 |
| 4  | - |
| 5  | - |
S= 32

| m2 | m1 |
|:----: | :----: |
| 11 | d=33 |
| 19 | - |
| 3  | - |
| 17 | d=33 |
| 7  | - |
| 8  | - |
| 1  | - |
S= 66


#### Q5.1

On sait que: Partition est NP-dur, JSP est NP, Part se réduit en JSP,
 
 ==> JSP est NP-complet
 
 
#### Q5.2

Non, car JSP prend en compte plus de 2 machines, alors que Partition utilise que 2. 

#### Q6 : Reduction: SUM
#### Q.6.1 : Reduction: SUM

Il existe un certificat, tel que;

    tab: tableau de taille k (1 <= k <= n) 
    Algo de verif:
    entrée: certificat de taille k, entier S: cible
    var : sum = 0 : entier
    debut
    
        pour i de 0 à k faire
            sum += certif[i]
        fpour 
    
        si (sum == S) alors
            retour vrai
        sinon
            retour faux
        fsi
    fin
    
compx(Algo de verif) = O(k)  
compx(entrée) = O(n) 

==> compx(Algo de verif) <= compx(entrée)  
**Donc Sum est NP.**

#### Q.6.2 : Red en Partition

SUM => red(I) => partition

    Algo: red  
    entrées: tab: tableau de n entiers, C: entier cible
    var: new_elem : entier
    debut
        new_elem = SOMME(tab) - 2*C
        tab[n] = new_elem // ajout de l'elem
        Parition(tab, n+1)
    fin

C = 11  
tab: [12, 4, 7, 4, 5]  
tab: [12, 4, 7, 4, 5, [22-32=10]]  
part(tab) (s/2 = 42/2 = 21 = d) =>  
[12, 4, 5] = [7 + 4 + 10]
