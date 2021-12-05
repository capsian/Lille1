ACT - TP3
---------------

##### Selim Lakhdar  
##### Jonathan Soleillet  



 COMPILATION + TEST  
 -------
	make
	make test

#### Q1

Un tableau à 2 dim, de taille :   
Nb_tâches * 2

| | début | machine |
|:----: | :----: | :----: |
| t1 | 2 | 1 |
| t2 | 0 | 1 |
| t3 | 6 | 2 |
| t4 | 4 | 1 |
| t5 | 0 | 2 |

La taille est bien bornée polynomialement par rapport à la taille de l'entrée.


#### Algo_Valide_Certif: 


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
	    tier(tab_machines[m])  // trier par d_i
	    verif(tab_machines[m]) // d_i + t_i <= d_i+1 
	  fpour  
	fin

==> O(nlogn)

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

Création d'un arbre avec toutes les valeurs possibles.  
Parcours en profondeur; chaque branche est un certificat possible.

==> fichier tests/out.ps 

==> O(((d+1)*nb_m)^nb_t)
   
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
            m = 2
            // init matrix
            pour i de 0 à n+2 faire
                matrix[i][0] = tab[i] 
                matrix[i][1] = tab[i]   // rand
            fpour
            
            JSP(m,matrix,d)
        fin


#### Q5.1

Partition est NP-dur, comme Parition est aussi NP ;
 
 ==> Parition est NP-complete 
 
 
#### Q5.2

Non, car JSP prend en compte plus de 2 machines, alors que Partition utilise que 2. 

#### Q6 : Reduction: SUM
#### Q.6.1 : Reduction: SUM

Il existe un certificat, tel que;

    tab: tableau de taille k (1 <= k <= n) => O(k.log(x_i))
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