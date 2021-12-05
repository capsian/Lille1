set VEG;
set ANIMAUX;

param surface_totale >= 0;

param vegetale_consommation{VEG,ANIMAUX}>= 0;
param vegetale_rendement{VEG} >= 0;  
param vegetale_prix_vente {VEG} >= 0;
param vegetale_vente_max {VEG} >= 0;

param animal_profit {ANIMAUX} >= 0;
param animal_surface_paturage {ANIMAUX} >= 0;

#capacité max pour le hangar (selon le type d'animal)
param hangar_limit {ANIMAUX} >= 0;
param hangar_nb  >= 0;
param hangar_porfit >= 0;

var animal_nb {a in ANIMAUX} integer>=0;
var vegetale_surface_cultivable {v in VEG} >= 0,<=surface_totale ;

var vegetale_qte_consomee {v in VEG} >= 0;
var vegetale_qte_produite{v in VEG} >=0;
var vegetale_qte_vendue{v in VEG} >=0;

var hangar_used integer >=0,<=5;


subject to limit_vente_vegetale {v in VEG} :
	vegetale_qte_vendue[v] = vegetale_qte_produite [v] - (sum {a in ANIMAUX} vegetale_consommation [v, a] * animal_nb [a]);
    
subject to limit_production_vegetale {v in VEG} :
	vegetale_qte_produite [v] = vegetale_surface_cultivable [v] * vegetale_rendement [v];
    
subject to limit_surface_totale :
	(sum {v in VEG} vegetale_surface_cultivable [v]) + (sum{a in ANIMAUX} animal_nb[a]*animal_surface_paturage[a]) = surface_totale;

subject to limit_vente_max {v in VEG}:
	vegetale_qte_vendue[v] <= vegetale_vente_max[v];

subject to conso_animaux {v in VEG} :
    vegetale_qte_consomee[v] = vegetale_qte_produite [v] - (sum {a in ANIMAUX} vegetale_consommation [v, a] * animal_nb[a]);
     
subject to hangar_used :
    hangar_used >= (sum {a in ANIMAUX} animal_nb[a] / hangar_limit[a]);
    
maximize profit  :
(sum {v in VEG} vegetale_qte_vendue[v] * vegetale_prix_vente[v])+ (sum{a in ANIMAUX}(animal_nb[a]*animal_profit[a]))+((hangar_nb-hanger_used)*hangar_porfit);


data;
set VEG := betterave ble mais;
set ANIMAUX := vache mouton ;

param surface_totale := 200;
param hangar_limit := 20;
param hangar_nb := 5;
param hangar_porfit := 1500;

param: 						
					vegtale_rendement  vegtale_vente_max vegtale_prix_vente:=
betterave   1            10       100
ble         0.6          20       120
mais				0.5          20       90;
    
param consommation :
             vache  mouton :=
  betterave  0.6     0.8
  ble        0.2     0.1
  mais       0.2     0.3  ;
               
param: hangar_limit  animal_profit  animal_surface_paturage:=
vache   20         200           2
mouton  29         150           1 ;        
