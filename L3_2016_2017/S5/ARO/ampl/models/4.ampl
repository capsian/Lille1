set VEG;
set ANIMAUX;
set CHOIX;

param nb_choix >= 1;

param veg_rendement {VEG} >= 0;
param veg_consommation {VEG,ANIMAUX} >= 0;
param veg_vente_max {VEG} >= 0;
param veg_prix_vente {VEG} >= 0;

param limit_animaux_are {ANIMAUX} >= 0;
param surface_totale >= 0;

param profit_animal {ANIMAUX} >= 0;
param hangar_capacite {ANIMAUX} >=0;

param hangar_nb >=0;
param hangar_loyer >=0;
var hangar_nb_used integer >=0;

var nb_animaux {ANIMAUX} >= 0;
var surface_paturage {ANIMAUX} >= 0;
var surface_cultivee {VEG} >= 0;

var veg_qte_consomee {VEG} >= 0;
var veg_qte_produite {VEG} >= 0;
var veg_qte_vendue {VEG} >= 0;

var isUsed {ANIMAUX} >= 0;

maximize objectif :
	sum {a in ANIMAUX} (nb_animaux[a] * profit_animal[a]) + sum {v in VEG} veg_qte_vendue [v] * veg_prix_vente [v] + (hangar_nb-hangar_nb_used) * hangar_loyer;

subject to limite_surface_totale {a in ANIMAUX} :
	surface_paturage[a] + sum {v in VEG} surface_cultivee[v] <= surface_totale;

subject to limite_surface_paturage {a in ANIMAUX} :
 nb_animaux[a] * limit_animaux_are[a] = surface_paturage[a];
	
subject to limite_rendement {v in VEG} :
	veg_qte_produite [v] = surface_cultivee [v] * veg_rendement [v];
	
subject to conso_animaux {a in ANIMAUX, v in VEG} :
	(nb_animaux[a] * veg_consommation[a,v]) = veg_qte_consomee [a,v];
	
subject to veg_limite_vente {v in VEG} :
	veg_vente_max [v] >= veg_qte_vendue[v];
	
subject to qte_produite {v in VEG} :
	veg_qte_produite[v] = veg_qte_consomee[v] + veg_qte_vendue[v];
	
subject to hangar_limit {a in ANIMAUX}:
	hangar_capacite[a] * hangar_nb_used >= nb_animaux[a];

subject to one_animal :
	sum{a in ANIMAUX} isUsed[a] = 1;
		

data;
param hangar_loyer := 1500;
param hangar_nb := 5;
param surface_totale := 200;
param nb_choix := 2;

set VEG := betterave ble mais;
set ANIMAUX := mouton vaches;
set CHOIX := 1..nb_choix;

param limit_animaux_are :=
	vache 2
	mouton 1;
	
param hangar_capacite :=
	vache 20
	mouton 29;

param profit_animal :=
	vache	200
	mouton	150;

param veg_consommation:		vache mouton:=
			betterave						0.6		0.8
			ble									0.2		0.1
			mais								0.2		0.3;

param:	veg_rendement	 veg_vente_max veg_prix_vente:=
betterave	1								10							100
ble				0.6							20							120
mais			0.5							20							90;
