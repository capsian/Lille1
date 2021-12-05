# TP IMG : Tatouage d'image par étalement de spectre

## Author
* Selim Lakhdar <selim.lakhdar@gmail.com> <selim.lakhdar.etu@univ-lille.fr>


## II. Filtres de contours

- Les images doivent être codées en 32-bit car on utilise les valeurs des dérivées, qui peuvent être négatives.

- sobel.ijm

- Le filtre appliqué fait ressortir les contours de l'image. Pour cela on utilise les deux images résultantes de la dérivée de l'image originale pour les deux composantes (x et y).

## III. Tatouage par étalement de spectre

![psnr=10](./output/WmkImage_tpsnr10.pgm)

- 4: On constate qu'un "calque" visible est superposé sur l'image. À partir d'un PSNR supérieur à 30 on ne remarque plus le tatouage.

- La fonction makeWmkSignal va prendre en entrée :  
	* msg: le message à crypté  
	* widthImg,heightImg: La taille de l'image  
	* IDcarriers: ID de l'image qui contient les porteuses.  
- La fonction va d'abord construire le vecteur de tatouage. Puis va découper l'image en tuiles.
```
function makeWmkSignal(IDcarriers,widthImg,heightImg,msg)
{
	selectImage(IDcarriers);
	getDimensions(widthTile, heightTile, channels, Nc, frames);
	
	newImage("WmkSignal", "32-bit black", widthImg, heightImg, 1);
	IDWmk = getImageID();

	newImage("WmkTile", "32-bit black", widthTile, heightTile, 1);
	IDWmkTile = getImageID();

	// Construction du vecteur de tatouage
	/* Spread-Spectrum */
	for(i=0; i< Nc; i++) {
		selectImage(IDcarriers);
		//indexes of stacks start at 1!!
		setSlice(i+1);
		if (msg[i] == 1)
			run("Multiply...", "value=-1 slice");
		imageCalculator("Add 32-bit", IDWmkTile, IDcarriers);
	}

	selectImage(IDWmkTile);

	/* update display LUT */
	resetMinAndMax();

	
	// Décomposer l'image en tuiles	
	makeRectangle(0, 0, widthTile, heightTile);
	run("Copy");
	run("Select None");	
	selectImage(IDWmk);
	for(j = 0 ; j < widthImg; j = j + widthTile) {
		for(i = 0 ; i < heightImg; i = i + heightTile) {
			makeRectangle(j, i, widthTile, heightTile);
			run("Paste");
		}
	}
	run("Select None");

	

	return IDWmk;
}
```   


- wnk_template.ijm

## IV. Robustesse du schéma de tatouage

- Oui. À partir d'un bruit d'écart type 110. L'image doit être complétement dégradé pour ne plus pouvoir décoder !!

