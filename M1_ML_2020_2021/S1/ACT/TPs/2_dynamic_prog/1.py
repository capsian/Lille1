import sys
import copy

# Input
n = int(input())
m = int(input())
init_config = []
tmp_input = []
for c in sys.stdin.read():
    if c == '\n':
        if len(tmp_input) > 0:
            init_config.append(tmp_input)
        tmp_input = []
        continue
    tmp_input.append(c)


def isWinConfig(config):
    if 'P' in config[0]:
        return True
    if 'p' in config[len(config) - 1]:
        return True
    return False


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


def best_score(scores):
    m = min(scores)
    if m > 0:
        return (max(scores) + 1) * -1

    max_min = m
    for e in sorted(scores):
        if e <= 0:
            if e > max_min:
                max_min = e

    return (max_min * -1) + 1

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


print(score(init_config, True))