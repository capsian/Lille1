set VEG;

param veg_rendement {VEG} >= 0;
param veg_consommation {VEG} >= 0;
param veg_vente_max {VEG} >= 0;
param veg_prix_vente {VEG} >= 0;

param surface_totale >= 0;
param profit_mouton >= 0;
param nb_mouton_are >=0;

param hangar_nb >=0;
param hangar_loyer >=0;
param hangar_limit_mouton >=0;
var hangar_nb_used integer >=0;

var nb_mouton integer >= 0;
var surface_paturage >= 0;
var surface_cultivee {VEG} >= 0;

var veg_qte_consomee {VEG} >= 0;
var veg_qte_produite {VEG} >= 0;
var veg_qte_vendue {VEG} >= 0;

maximize objectif :
 (profit_mouton*nb_mouton) +sum {v in VEG} veg_qte_vendue [v] * veg_prix_vente [v] + (hangar_nb-hangar_nb_used) * hangar_loyer;

subject to limite_surface_totale :
	surface_paturage + sum {v in VEG} surface_cultivee[v] <= surface_totale;

subject to limite_surface_paturage :
	(nb_mouton * nb_mouton_are) = surface_paturage;
	
subject to limite_rendement {v in VEG} :
	veg_qte_produite [v] = surface_cultivee [v] * veg_rendement [v];
	
subject to conso_mouton {v in VEG} :
	nb_mouton * veg_consommation[v] = veg_qte_consomee [v];
	
subject to veg_limite_vente {v in VEG} :
	veg_vente_max [v] >= veg_qte_vendue[v];
	
subject to qte_produite {v in VEG} :
	veg_qte_produite[v] = veg_qte_consomee[v] + veg_qte_vendue[v];
	
subject to hangar_limit :
	hangar_limit_mouton * hangar_nb_used >= nb_mouton;
	

	

data;
param hangar_limit_mouton := 29;
param hangar_loyer := 1500;
param hangar_nb := 5;
param surface_totale := 200;
param profit_mouton := 150;
param nb_mouton_are := 1;
set VEG := betterave ble mais;
param:	veg_rendement	veg_consommation veg_vente_max veg_prix_vente:=
betterave	1	0.8	10	100
ble	0.6	0.1	20	120
mais	0.5	0.3	20	90;
