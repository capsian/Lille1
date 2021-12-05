# TP2 Programmation dynamique: Hexapawn

## Author

* Selim Lakhdar <selim.lakhdar@gmail.com> <selim.lakhdar.etu@univ-lille.fr>

## Formule

Suivant la liste des scores des successeurs nous pouvons calculer le score de la configuration actuelle:

 - Si tous les scores sont positifs:
    * retourner: (max(scores) + 1) * -1
 - Si on a des scores negatifs:
    * retourner: (max_neg(score) * -1 ) + 1
        * max_neg: retourne la valeur négative la plus grande
            * [-15, -2, 15 ] => retourne -2
            
            
## Algo

### score
```
def score(config, player):
    if isWinConfig(config):
        return 0
    if cantMove(config):
        return 0

    moves = getMoves(config, player)

    scores = []
    for mv in moves:
        scores.append(score(mv, not player))

    return best_score(scores)
```   

### Moves
```
def getMoves(config, player):
    tmp_moves = []

    for i in range(n):
        for j in range(m):
            if player:
                if config[i][j] == "P":
                    tmp_moves.append(moveForward(i, j, config))
                    tmp_moves.append(eatRight(i, j, config))
                    tmp_moves.append(eatLeft(i, j, config))
            else:
                if config[i][j] == "p":
                    tmp_moves.append(moveForward(i, j, config))
                    tmp_moves.append(eatRight(i, j, config))
                    tmp_moves.append(eatLeft(i, j, config))

    # remove empty
    tmp_moves = [var for var in tmp_moves if var]
    return tmp_moves
```
#### Move Forward

```
def moveForward(pos_i, pos_j, config):
    # White
    if config[pos_i][pos_j] == "P":
        if config[pos_i - 1][pos_j] == " ":
            res = copy.deepcopy(config)
            res[pos_i][pos_j] = " "
            res[pos_i - 1][pos_j] = "P"
            return res
    # Black
    if config[pos_i][pos_j] == "p":
        if config[pos_i + 1][pos_j] == " ":
            res = copy.deepcopy(config)
            res[pos_i][pos_j] = " "
            res[pos_i + 1][pos_j] = "p"
            return res
    return []

```

#### Eat
```
def eatRight(pos_i, pos_j, config):
    # White
    if config[pos_i][pos_j] == "P":
        if pos_j < m - 1:
            if config[pos_i - 1][pos_j + 1] == "p":
                res = copy.deepcopy(config)
                res[pos_i][pos_j] = " "
                res[pos_i - 1][pos_j + 1] = "P"
                return res
    # Black
    if config[pos_i][pos_j] == "p":
        if pos_j < m - 1:
            if config[pos_i + 1][pos_j + 1] == "P":
                res = copy.deepcopy(config)
                res[pos_i][pos_j] = " "
                res[pos_i + 1][pos_j + 1] = "p"
                return res
    return []


def eatLeft(pos_i, pos_j, config):
    # White
    if config[pos_i][pos_j] == "P":
        if pos_j > 0:
            if config[pos_i - 1][pos_j - 1] == "p":
                res = copy.deepcopy(config)
                res[pos_i][pos_j] = " "
                res[pos_i - 1][pos_j - 1] = "P"
                return res
    # Black
    if config[pos_i][pos_j] == "p":
        if pos_j > 0:
            if config[pos_i + 1][pos_j - 1] == "P":
                res = copy.deepcopy(config)
                res[pos_i][pos_j] = " "
                res[pos_i + 1][pos_j - 1] = "p"
                return res
    return []
```

#### Cas de bases
##### isWinConfig
Vérifie si la configuration est gagnante (ie: un pion blanc (inv noir) sur la dernière ligne des pions noir (inv blanc))
```
def isWinConfig(config):
    if 'P' in config[0]:
        return True
    if 'p' in config[len(config) - 1]:
        return True
    return False
```
##### cantMove
Vérifie si la configuration est bloquée (ie: On ne peut plus bouger de pions (que ce soit noir ou blanc))
```
def cantMove(config):
    moved_black = False
    moved_white = False
    for i in range(n):
        for j in range(m):
            if len(moveForward(i, j, config)) > 0 or len(eatRight(i, j, config)) > 0 or len(eatLeft(i, j, config)) > 0:
                if config[i][j] == "P":
                    moved_white = True
                elif config[i][j] == "p":
                    moved_black = True
            if moved_black and moved_white:
                return False

    return True
```

## Version dynamique

Afin de ne plus calculer les configurations redondantes, on utilise un dictionnaire (hashmap) qui va stocker une config sous forme de hash en lui assosiant son score.

```
dict = {}
def score(config, player):

    h = hash(str(config) + str(player))
    if h in dict.values():
        return dict[h]

    if isWinConfig(config):
        return 0
    if cantMove(config):
        return 0

    moves = getMoves(config, player)

    scores = []
    for mv in moves:
        scores.append(score(mv, not player))

    dict[h] = best_score(scores)
    return best_score(scores)
```
