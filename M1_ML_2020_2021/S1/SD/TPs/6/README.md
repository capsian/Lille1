# TP6 SD - Classification

## Author
* Selim Lakhdar <selim.lakhdar.etu@univ-lille.fr> <selim.lakhdar@gmail.com>

## CR
### Classification

- Le TP a été plutôt simple à suivre.

- J'ai eu des problèmes avec la classification avec les attributs catégoriels. La feature CA pose un problème. Lors de la prédiction une erreur survient:
```
	IndexError: index 4 is out of bounds for axis 1 with size 4
```

- D'après mes recherches, ceci pourrait être dû à des valeurs (ici de CA) qui n'apparaissent que dans le train (inv test) mais pas dans le test (inv train). (https://github.com/scikit-learn/scikit-learn/issues/16028 ??)

- Concernant le scaling, j'ai obtenu un score de 1, ce qui me parrait suspect ... (ou pas ??)
