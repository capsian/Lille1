import numpy as np


def display_grid(grid):
    for i in range(grid.shape[0]):
        for j in range(grid.shape[1]):
            print(grid[i,j], '  ', end='')
        print()


def generate_environement(nb_actors, nb_objects, w=10, h=10):

    l1 = [['.'] * w] * h
    grid = np.array(l1, dtype=object).reshape(w,h)

    actors_pos = []
    object_pos = []
    destination_pos = []

    # place objects
    for i in range(nb_objects):
        placed = False
        while not placed:
            x_i = np.random.randint(0, high=w)
            x_j = np.random.randint(0, high=h)
            if grid[x_i, x_j] == '.':
                placed = True
                grid[x_i, x_j] = 'O'
                object_pos += [[x_i, x_j]]

    # place objects
    for i in range(nb_actors):
        placed = False
        while not placed:
            x_i = np.random.randint(0, high=w)
            x_j = np.random.randint(0, high=h)
            if grid[x_i, x_j] == '.':
                placed = True
                grid[x_i, x_j] = 'A'
                actors_pos += [[x_i, x_j]]

    # place destination
    placed = False
    while not placed:
        x_i = np.random.randint(0, high=w)
        x_j = np.random.randint(0, high=h)
        if grid[x_i, x_j] == '.':
            placed = True
            grid[x_i, x_j] = 'D'
            destination_pos += [x_i, x_j]


    return grid, actors_pos, object_pos, destination_pos



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




grid, actors_pos, object_pos, destination_pos = generate_environement(5,20)
display_grid(grid)
print("----------------------------")
print("selected actor: ", actors_pos[0])
print("selected object: ", object_pos[0])
print("----------------------------")
simulator(grid, actors_pos[0], object_pos[0], destination_pos, ['U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'])