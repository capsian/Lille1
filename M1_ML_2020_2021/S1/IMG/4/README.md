# TP IMG : transformations locales des images

## Author
* Selim Lakhdar <selim.lakhdar@gmail.com> <selim.lakhdar.etu@univ-lille.fr>

## CR

### Définition et application d'un filtre moyenneur

Le filtre appliqué, rend l'image plus claire.

0	0	0	0	0	0	0
0	0	0	0	0	0	0
0	0	180	180	180	0	0
0	0	180	180	180	0	0
0	0	180	180	180	0	0
0	0	0	0	0	0	0
0	0	0	0	0	0	0

-------

0	0	0	0	0	0	0
0	180	255	255	255	180	0
0	255	255	255	255	255	0
0	255	255	255	255	255	0
0	255	255	255	255	255	0
0	180	255	255	255	180	0
0	0	0	0	0	0	0

pxl: 255 = 180 * 9 => prendre la val max: 255
pxl: 180 = 180 + 8 * 0 => 180

==============================


0	0	0	0	0	0	0
0	0	0	0	0	0	0
0	0	180	180	180	0	0
0	0	180	180	180	0	0
0	0	180	180	180	0	0
0	0	0	0	0	0	0
0	0	0	0	0	0	0

-------

0	0	0	0	0	0	0
0	20	40	60	40	20	0
0	40	80	120	80	40	0
0	60	120	180	120	60	0
0	40	80	120	80	40	0
0	20	40	60	40	20	0
0	0	0	0	0	0	0

pxl: 20 = 180/9
pxl: 40 = (180*2)/9
...

Le filtre devient 1/9 [ [1,1,1], [1,1,1], [1,1,1] ]

### Effets de bords

0	0	0	0	0	0	0
0	0	0	0	0	0	0
0	0	255	180	180	0	0
0	0	255	180	180	0	0
0	0	255	180	180	0	0
0	0	0	0	0	0	0
0	0	0	0	0	0	0

----

0	0	0	0	0	0	0
0	28	48	68	40	20	0
0	57	97	137	80	40	0
0	85	145	205	120	60	0
0	57	97	137	80	40	0
0	28	48	68	40	20	0
0	0	0	0	0	0	0


pxl 28: 255 / 9
pxl 145: ((180*3)+(255*3))/9

ImageJ rajoute une colonne de 0.

### Bruit Gaussien d'une image synthétique

- D'après l'histogramme l'écart-type n'est plus égal à 0. Il y a plus de de nuances  de gris. Bruit Gaussien additif (d'amplification).

- Avec le filtre H1 non normalisé, l'image devient blanche. (éclaircit l'image ?)
- Avec le filtre H1 normalisé, l'image devient floue.


### Filtres moyenneurs sur une image naturelle

- La nuance de gris est plus prononcée. Les deux pics de pixels aux points 0 et 127 se sont élargies.

- L'image devient de plus en plus floue. La moyenne des pixels est plus élevée (~70 => ~80), et l'écart type plus bas (~60 => ~50).

- On remarque que l'image devient de plus en plus floue. La moyenne des pixels est plus élevée, et l'écart type est plus bas.

### Bruit impulsionnel et filtre médian

- Il ya plus de pixels étalés entre les valeurs 50 et 200. L'écart type n'est plus nul mais la moyenne des pixels est la même. Bruit Gaussien additif (d'amplification).

- Les filtres, moyenneur et Gaussien rendent l'image plus floue. Ces filtres ne sont pas efficaces pour réduire ce type de bruit.

- Le filtre médian rend l'image floue.

- 

### Macro

n = 2;
list = newArray(n);
for (i=1; i<=n; i++)
{
    selectImage(i);
    list[i-1] = getTitle();
}


Dialog.addChoice("First image:", list);
Dialog.addChoice("Second image:", list);
Dialog.show();
image1 = Dialog.getChoice();
image2 = Dialog.getChoice();

selectImage(image1);
heightImg1 = getHeight();
widthImg1 = getWidth();

selectImage(image2);
heightImg2 = getHeight();
widthImg2 = getWidth();

for(i = 0 ; i < widthImg1; i++) {
        for(j = 0 ; j < heightImg1; j++) {
        	selectImage(image1);
        
        	// GET MIN MAX
            p1 = getPixel(i-1,j-1);
            pmin = p1
            pmax = p1 
            p2 = getPixel(i,j-1);
            if (p2 < pmin) { pmin = p2 }
            if (p2 > pmax) { pmax = p2 }
            p3 = getPixel(i+1,j-1);
            if (p3 < pmin) { pmin = p3 }
            if (p3 > pmax) { pmax = p3 }
            
            p4 = getPixel(i-1,j);
            if (p4 < pmin) { pmin = p4 }
            if (p4 > pmax) { pmax = p4 }
            p5 = getPixel(i,j);
            if (p5 < pmin) { pmin = p5 }
            if (p5 > pmax) { pmax = p5 }
            p6 = getPixel(i+1,j);
            if (p6 < pmin) { pmin = p6 }
            if (p6 > pmax) { pmax = p6 }
            
            p7 = getPixel(i-1,j+1);
            if (p7 < pmin) { pmin = p7 }
            if (p7 > pmax) { pmax = p7 }
            p8 = getPixel(i,j+1);
            if (p8 < pmin) { pmin = p8 }
            if (p8 > pmax) { pmax = p8 }
            p9 = getPixel(i+1,j+1);
            if (p9 < pmin) { pmin = p9 }
            if (p9 > pmax) { pmax = p9 }
            
            // SET MIN MAX  
            selectImage(image2);          
            if (p1 < pmin ) {  setPixel(i-1, j-1, pmin) }
            elfe if (p1 > pmax) { setPixel(i-1, j-1, pmax) }
            
            if (p2 < pmin ) { setPixel(i,j-1, pmin) }
            elfe if (p2 > pmax) { setPixel(i,j-1, pmax) }
            
            if (p3 < pmin ) { setPixel(i+1,j-1, pmin) }
            elfe if (p3 > pmax) { setPixel(i+1,j-1, pmax) }
            
            if (p4 < pmin ) { setPixel(i-1,j, pmin) }
            elfe if (p4 > pmax) { setPixel(i-1,j, pmax) }
            
            if (p5 < pmin ) { setPixel(i, j, pmin) }
            elfe if (p5 > pmax) { setPixel(i, j, pmax) }
            
            if (p6 < pmin ) { setPixel(i+1,j, pmin) }
            elfe if (p6 > pmax) { setPixel(i+1,j, pmax) }
            
            if (p7 < pmin ) { setPixel(i-1,j+1, pmin) }
            elfe if (p7 > pmax) { setPixel(i-1,j+1, pmax) }
            
            if (p8 < pmin ) { setPixel(i,j+1, pmin) }
            elfe if (p8 > pmax) { setPixel(i,j+1, pmax) }
            
            if (p9 < pmin ) { setPixel(i+1,j+1, pmin) }
            elfe if (p9 > pmax) { setPixel(i+1,j+1, pmax) }
            
        }
    }
