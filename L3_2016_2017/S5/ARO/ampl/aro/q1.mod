set VEG;
param consommation{VEG}>= 0;
param rendement{VEG} >= 0;
param prix_vente {VEG} >= 0;
param vente_max {VEG} >= 0;
param are :=200;
var qte_vache integer>=0;
var are_veg {v in VEG} >= 0 ;

subject to are_limitee :
(sum {v in VEG} are_veg [v]) + qte_vache*2 <=are;
subject to limit_vache_con {v in VEG}:
are_veg[v]*rendement[v] >= consommation[v]*qte_vache; 
subject to limit_vent_max {v in VEG}:
are_veg[v]*rendement[v]-consommation[v]*qte_vache <= vente_max[v];
maximize profit :
(sum {v in VEG} ((are_veg[v]*rendement[v]-consommation[v]*qte_vache) * prix_vente[v]))+(qte_vache*200);
data;
set VEG := betterave ble mais  ;


param: rendement consommation vente_max prix_vente:=
betterave
         1         0.6         10       100
ble
         0.6       0.2         20       120
mais
         0.5       0.2         20       90 ;