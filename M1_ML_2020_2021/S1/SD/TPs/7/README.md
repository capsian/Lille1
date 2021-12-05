# TP7 SD - Temps et Mesures

## Author
* Selim Lakhdar <selim.lakhdar.etu@univ-lille.fr> <selim.lakhdar@gmail.com>

## CR
### Temps et Mesures

- Je ne suis pas arrivé à dessiner les courbes finales.

- J'ai bien utilisé le OneVsRestClassifier ainsi que le label_binarize sur ys_train. (et même sur tout le dataset)
```
	from sklearn.preprocessing import label_binarize
	from sklearn.multiclass import OneVsRestClassifier

	ys_train_1 = label_binarize(ys_train, classes=np.arange(0,10))

	# Run classifier
	classifier = OneVsRestClassifier(LogisticRegression())
	classifier.fit(Xs_train, ys_train_1)
	y_score = classifier.decision_function(Xs_test)

	print(y_score)
	print(ys_test)
```

- J'ai eu plusieurs erreurs:
```
	UserWarning: Label not 0 is present in all training examples.
	UserWarning: Label not 1 is present in all training examples.
	.....
	UserWarning: Label not 9 is present in all training examples.
```

- ==> Tous les scores sont à 0 :(

- J'ai aussi utilisé LabelEncoder, mais j'y suis pas arrivé :/
