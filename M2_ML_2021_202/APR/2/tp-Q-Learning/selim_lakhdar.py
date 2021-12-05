import labyrinthe
import numpy as np

laby = labyrinthe.Labyrinthe (filename='laby.1', x=1, y=1)
laby.reset()


def q_learning(lab, episode=200, gamma=0.9, eps=1):
    nb_actions = 4
    nb_state = lab.hauteur * lab.largeur

    q_star = np.zeros((nb_state, nb_actions))
    n = np.zeros((nb_state, nb_actions))

    stop = False
    while not stop:
        for _ in range(episode):
            # init
            lab.reset()
            t = 0
            done = False
            while not done:



q_learning(laby)
