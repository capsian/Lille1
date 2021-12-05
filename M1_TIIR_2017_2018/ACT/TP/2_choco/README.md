# TP2 : TP Chocolat

---
Groupe 5 M1 Info    
Jonathan Soleillet Selim Lakhdar


Compilation
-----

`cd src && make`

-----
**Question 1**


        +3
      /  \  \
     /    \  \
    +1_  -2---+1
     | \  |   |
     |  \ |   |
     |   \+1  |
     |    |   |
      \   |  /
       \  | /
          0

-----------
**Question 2**

- Cas où tous les successeurs sont positifs :   
`score = -max(|succ+|) -1`

- Autre cas :   
 `score = max (|succ-|) +1`
 

-----------
**Question 3**

- time f(10,7,7,3) :   
`4.5s`

- time f(10,7,5,3) :   
 `9.6s` 
 
-----------
**Question 4**

- f(10,7,7,3) :  
_11   
 real    0m4,499s   
 user    0m4,492s  
 sys     0m0,000s_

- f(10,7,5,3) :   
_15   
 real    0m9,688s   
 user    0m9,680s  
 sys     0m0,000s_

------
**Question 5**

Les paires de (i,j) qui nous retournes 127 sont :   
`(0,63) (63,0) (63,126) (126,63)`  
Si on a une taille de n = m impair on aura les configurations donnant n (ou m) :  
`(0,n-1/2) (n-1/2,0) (n-1/2,n-1) (n-1,n-1/2)`

-------
**Question 6**

A chaque appel de f on effectue !(n) + !(m) appels à f

-------
**Question 7**

Car nous effectuons une simple rotation de la plaque

-------
**Question 9**

nous divisons par n/2