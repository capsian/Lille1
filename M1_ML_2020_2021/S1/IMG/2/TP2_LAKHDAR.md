# TP2

## Author
- Selim Lakhdar

## Rendu

### Définition et résolution

- Définition:  500*580 pxl

- C'est image de 500*580 pixels, codée sur 8 bit.

- x,y: coordonées de chaque pxl
  w,h: la longueur et la largeure du rectangle (selection)
  
- Res Verticale:
	1cm = 40pxl
	on a 580pxl, 580/40 = 14.5cm
	=> 580 / 14.5 = 40 ddp
	
- Res Horizontale:
	1cm = 40pxl
	on a 500pxl, 500/40 = 12.5cm

- Pixel size: 1x1 pixel^2
- Size:  500*580*8*1 =  2320000 bits

- Après avoir changer de résolution, on constate que l'image se détériore (les chiffres ne sont pas tous visibles) et la taille a diminué.
- La nouvelle image a été créer en compressant la première. ie: pour une même unitée (un carré de 9pxl) on ne prend que la moitié des pxl (??)

- Res Vert:
	1cm = 20pxl
	on a 290pxl, 290/20 = 14.5cm
	=> 290 / 14.5 = 20
- Res  Horizontale:
	=> 250 / 12.5 = 20
	
- L'image apparait comme l'élargissement de l'ancienne image. Sans reconstruction des pxl manquants.
- => Le processus ne fait que "applatir" l'image. 

- => L'image est complétement dégardée. On ne voit plus la règle.

### Extraction des composantes

- Les 3 images se différencient dans l'intensité des coleurs (niveau de gris).

### Combinaison des composantes

- a = RED + GREEN (only)
- b = RED + BLUE
- b = 

### Variation de quantification

- Sachant qu'un pxl de l'image est codé sur 8bit: 256 valeurs possible. Cette opération va masquer 4 bits de chaque pixel, l'information sera donc codée sur 4 bits seuelement: 2^4 ==> 16 valeurs possible pour chaque pxl (0->17).

- Pour l'image originale on a:
	512 * 512 * 3 * 8 = 6291456
 => après opération on a
   	(512 * 512 * 7) + (512 * 512 * 5) + (512 * 512 * 4) = 4194304


### Sous­ échantillonnage

- On réduit l'image de 512*512 à 256*256 => on prend 1px sur 2. Puis on repasse à 512*512 => on duplique chaque pixel.

-  Taille originale: 512 * 512 * 3 * 8 = 6291456
   Nouvelle taille: (512 * 512 * 8) + (256 * 256 * 8) + (256 * 256 * 8) = 3145728
   
- L'image est légérement dégradée comparée à la première. (Perte d'information)

- Si l'image est codée sur 8 bit et de taille 512*512
 - R:  
