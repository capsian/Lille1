import numpy as np


def display_grid(grid):
    for i in range(grid.shape[0]):
        for j in range(grid.shape[1]):
            print(grid[i,j], '  ', end='')
        print()



def step(grid, start_pos, action):

    new_pos_i, new_pos_j = start_pos[0], start_pos[1]
    done = False

    # process action
    if action == 'D': new_pos_i += 1
    if action == 'U': new_pos_i -= 1
    if action == 'R': new_pos_j += 1
    if action == 'L': new_pos_j -= 1

    print("step:", action, 'start_pos:', start_pos, 'new_pos_i:', new_pos_i, 'new_pos_j', new_pos_j)

    # check if we are not out of grid
    cond1 = new_pos_i >= grid.shape[0] or new_pos_j >= grid.shape[1]
    cond2 = new_pos_i < 0 or new_pos_j < 0
    if cond1 or cond2:
        print("setp error, out of grid")
        return grid, start_pos, False

    # return same pos if we encounter another actor or actor with object
    if grid[new_pos_i, new_pos_j] == 'A' or grid[new_pos_i, new_pos_j] == 'AO':
        print("Warning, found an actor in that cell !!")
        return grid, start_pos, False

    # take object if found
    if grid[new_pos_i, new_pos_j] == 'O' and grid[start_pos[0], start_pos[1]] != "AO":
        grid[new_pos_i, new_pos_j] = "AO"
    elif grid[new_pos_i, new_pos_j] == 'O':
        print("Warning can't take 2 objects")
        return grid, start_pos, False

    # drop object
    if grid[new_pos_i, new_pos_j] == 'D' and grid[start_pos[0], start_pos[1]] == "AO":
        grid[start_pos[0], start_pos[1]] = "A"
        return grid, start_pos, True
    elif grid[new_pos_i, new_pos_j] == 'D':
        print("Warning: actor trying to put invisible obj")
        return grid, start_pos, False

    # simple move
    if grid[new_pos_i, new_pos_j] == '.':
        grid[new_pos_i, new_pos_j] = grid[start_pos[0], start_pos[1]]

    # update actor old pos
    grid[start_pos[0], start_pos[1]] = '.'

    done = True
    return grid, [new_pos_i, new_pos_j], done




# actions = [a1, a2, a3, ..., an]
#   U:0, D:1, R:2, L:3
def simulator(grid, start_pos, target_pos, dest_pos, actions):

    # check start pos: need to be and actor
    if grid[start_pos[0], start_pos[1]] != 'A':
        print("simulator error: no actor found in pos", start_pos)
        return None

    # check target pos
    if grid[target_pos[0], target_pos[1]] != 'O':
        print("simulator error: no object found in pos", target_pos)
        return None

    # simulate
    new_grid = grid
    curr_pos = start_pos
    for a in actions:
        new_grid, curr_pos, done = step(new_grid, curr_pos, a)
        if not done:
            return -1
        display_grid(new_grid)
        print("==================")



w = 10
h = 10
l1 = [['.'] * w] * h
grid = np.array(l1, dtype=object).reshape(w,h)

actors_pos = []
object_pos = []
destination_pos = []

# place objects
grid[0, 0] = 'A'
grid[2, 5] = 'A'
grid[4, 6] = 'A'
grid[7, 7] = 'A'

# place objects
grid[5, 5] = 'O'
grid[2, 3] = 'O'
grid[6, 6] = 'O'
grid[8, 8] = 'O'
grid[9, 8] = 'O'

# place destination
grid[9, 9] = 'D'


display_grid(grid)
print("----------------------------")
simulator(grid, [4, 6], [8, 8], [9, 9], ['D', 'D', 'R', 'R', 'R', 'D', 'D', 'D', 'L', 'L', 'U'])
