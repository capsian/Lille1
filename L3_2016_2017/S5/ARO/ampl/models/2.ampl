set VEG;

param veg_rendement {VEG} >= 0;
param veg_consommation {VEG} >= 0;
param veg_vente_max {VEG} >= 0;
param veg_prix_vente {VEG} >= 0;

param surface_totale >= 0;
param profit_lait >= 0;
param nb_vaches_are >=0;

param hangar_nb >=0;
param hangar_loyer >=0;
param hangar_limit_vache >=0;
var hangar_nb_used integer >=0;

var nb_vaches integer >= 0;
var surface_paturage >= 0;
var surface_cultivee {VEG} >= 0;

var veg_qte_consomee {VEG} >= 0;
var veg_qte_produite {VEG} >= 0;
var veg_qte_vendue {VEG} >= 0;

maximize objectif :
	nb_vaches * profit_lait + sum {v in VEG} veg_qte_vendue [v] * veg_prix_vente [v] + (hangar_nb-hangar_nb_used) * hangar_loyer;

subject to limite_surface_totale :
	surface_paturage + sum {v in VEG} surface_cultivee[v] <= surface_totale;

subject to limite_surface_paturage :
	(nb_vaches * nb_vaches_are) = surface_paturage;
	
subject to limite_rendement {v in VEG} :
	veg_qte_produite [v] = surface_cultivee [v] * veg_rendement [v];
	
subject to conso_vaches {v in VEG} :
	nb_vaches * veg_consommation[v] = veg_qte_consomee [v];
	
subject to veg_limite_vente {v in VEG} :
	veg_vente_max [v] >= veg_qte_vendue[v];
	
subject to qte_produite {v in VEG} :
	veg_qte_produite[v] = veg_qte_consomee[v] + veg_qte_vendue[v];
	
subject to hangar_limit :
	hangar_limit_vache * hangar_nb_used >= nb_vaches;
	

	

data;
param hangar_limit_vache := 20;
param hangar_loyer := 1500;
param hangar_nb := 5;
param surface_totale := 200;
param profit_lait := 200;
param nb_vaches_are := 2;
set VEG := betterave ble mais;
param:	veg_rendement	veg_consommation veg_vente_max veg_prix_vente:=
betterave	1	0.6	10	100
ble	0.6	0.2	20	120
mais	0.5	0.2	20	90;
