# TP1 SD

## Author
* Selim Lakhdar <selim.lakhdar.etu@univ-lille.fr> <selim.lakhdar@gmail.com>

## CR

Le TP était plutôt simple à suivre. Vers la fin, les choses se compliquent un peu.
Je ne suis pas arrivé à retrouver la valeur score calculée par la fonction.
La formule est : 

```
u = ((y_true - y_pred) ** 2).sum()
v = ((y_true - y_true.mean()) ** 2).sum()
R^2 = (1 - u/v)
```

