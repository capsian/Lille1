set VEG;
set ANNEE;
param consommation{VEG}>= 0;
param rendement{VEG} >= 0;
param prix_vente {VEG} >= 0;
param vente_max {VEG} >= 0;
param are :=200;
var qte_vache{ANNEE} integer>=0;
var are_veg {v in VEG} >= 0 ;
var hanger_used integer >=0;
param subvention{ANNEE} >=0;

subject to are_limitee{a in ANNEE} :
(sum {v in VEG} are_veg [v]) + ( qte_vache[a]*2 )<=are;
subject to limit_vache_con {v in VEG,a in ANNEE}:
are_veg[v]*rendement[v] >= consommation[v]*qte_vache[a]; 
subject to limit_vent_max {v in VEG,a in ANNEE}:
are_veg[v]*rendement[v]-consommation[v]*qte_vache[a] <= vente_max[v];
subject to limit_hanger1{a in ANNEE}:
hanger_used*20>=qte_vache[a];
subject to limit_hanger2{a in ANNEE}:
(hanger_used-1)*20<=qte_vache[a];
maximize profit :
sum {v in VEG,a in ANNEE} ((are_veg[v]*rendement[v]-consommation[v]*qte_vache[a]) * prix_vente[v])+sum{a in ANNEE}(qte_vache[a]*200)+((5-hanger_used)*1500)*5+sum{a in ANNEE}(subvention[a]);
data;
set VEG := betterave ble mais  ;


param: rendement consommation vente_max prix_vente:=
betterave
         1         0.6         10       100
ble
         0.6       0.2         20       120
mais
         0.5       0.2         20       90 ;
set ANNEE :=2017 2018 2019 2020 2021;
 param   subvention :=   
   2017  450
   2018  280
   2019  170
   2020  500
   2021  220 ;   