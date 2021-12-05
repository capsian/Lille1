# TP3

## Author
- Selim Lakhdar

## Rendu

### Histogramme

- Taille: 400 * 289
- Profondeur: 8 Bits -> 0-255
- 400 * 289 * 3 = 

- La moyenne des pixels est de 76.38 avec un écart type de 62.5. L'image a une luminance faible et un contraste élevé.
- Gamme dynamique: [0 - 201]
- Information de Mode ?? (introuvable)
- pxl: 127, count: 1077

- pxls: [117-118-124-125]
- macro1_tp3.txt
```
Niveau maximal : 125
Moyenne : 121
ecartType : 4.0825
```
- ecartType [117-118-124-125]
=> moy = 1/4 [117 + 118 + 124 + 125] = 121
==> ecartType: sqrt( 1/4 * [(117 - 121)² + (118 - 121)² + (124 - 121)² + (125-121)²]) = 3.5
===> https://github.com/imagej/imagej1/blob/master/ij/process/ImageStatistics.java [l144]

### Seuillage

- Entre [50 - 60]
- macro2_tp3.txt
- Meilleur threshold: 55

- macro3_tp3.txt
- LUT:
	si i < 55 => i' = 0 (Pour tous les pixels < 55 => vont être mis à 0.)
	sinon i' = 255 (Pour tous les pixels > 55 => vont être mis à 255.)
	
- Les gateaux sont repréenté en blanc, il suffit de compte le nombre de pxl égale à 255. => 64176

- On utilise l'opération Add sur l'image gateaux1 et geteaux1-bin

- on remarque que l'image a une moyenne et un écrat type assez élevé => luminance et contraste élevé


### Transformations ponctuelles

- (macro4_tp3) Transformation: Expansion de la dynamique. D'après les histogrames ont remarque que les niveaux de gris sont plus étalés. La luminance a augmenté.

- On remarque que l'histograme est devenu plus "plat". Les niveaux de gris sont mieux étalés.

- Une transformation linéaire simple peut changer (dégrader) complétement l'image.

- macro6_tp3.txt

- macro7_tp3.txt 

### Égalisation d'histogramme

- macro8_tp3.txt

- L'allure de la courbe est croissante. Le niveau de gris n'est pas répartis de façon égale.

- On remarque que le contraste est plus élevé (la courbe est plus étalée). Une forte luminance (beaucoup de pxl de grande valeures (val:+200)
