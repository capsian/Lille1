// Calcul de la norme du gradient par masque de Sobel
//
requires("1.41i");	// requis par substring(string, index)
setBatchMode(true);	// false pour déboguer

/****** Création des images ******/
sourceImage = getImageID();
filename = getTitle();
extension = "";
if (lastIndexOf(filename, ".") > 0) {
    extension = substring(filename, lastIndexOf(filename, "."));
    filename = substring(filename, 0, lastIndexOf(filename, "."));
}
filenameDerX = filename+"_der_x"+extension; // images des
filenameDerY = filename+"_der_y"+extension; // dérivées
run("Duplicate...", "title="+filenameDerX);
run("Duplicate...", "title="+filenameDerY);

selectWindow(filenameDerX);
run("32-bit");	// conversion en Float avant calcul des dérivées !!
run("Convolve...", "text1=[-0.125 0 0.125\n-0.25 0 0.25\n-0.125 0 0.125\n] normalize");

selectWindow(filenameDerY);
run("32-bit");	// conversion en Float avant calcul des dérivées !!
run("Convolve...", "text1=[-0.125 -0.25 -0.125\n0 0 0\n0.125 0.25 0.125\n] normalize");

/****** Calcul de la norme du gradient ******/
// récupération de la taille de l'image
w = getWidth();
h = getHeight();
// Calculs pour chaque pixel
x_img = newArray(w*h); 
y_img = newArray(w*h); 

selectWindow(filenameDerX); 
for (y=0; y<h; y++) { 
        for (x=0; x<w; x++) { 
                x_img[x+(w*y)]=getPixel(x, y);
        } 
} 

selectWindow(filenameDerY); 
for (y=0; y<h; y++) { 
        for (x=0; x<w; x++) { 
                y_img[x+(w*y)]=getPixel(x, y); 
        } 
}

newImage("peppers_gradNorm", "8-bit", w, h, 1); 
for (y=0; y<h; y++) { 
        for (x=0; x<w; x++) {
        		val = Math.sqrt(y_img[x+(w*y)]*y_img[x+(w*y)] + x_img[x+(w*y)] * x_img[x+(w*y)]);
                setPixel(x, y, val); 
        } 
}


close(filenameDerX);
close(filenameDerY);

updateDisplay();
setBatchMode("exit and display");
