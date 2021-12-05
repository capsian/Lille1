import random
from gym import spaces

class Labyrinthe:
    def __init__(self, filename, name = "no name", x = -1, y = -1, rG = 10, rs = 0, null_mvt_flag = True):
        '''
        filename : fichier contenant le labyrinthe
        name : le nom donné au labyrinthe (pour faire joli)
        x, y = coordonnées initiales de l'agent
        xg, yg = coordonnées de la position à atteindre
        rG = retour quand position à atteindre est atteinte 
        rs = retour à chaque pas avant d'atteindre la position à atteindre
        '''
        self.ok = True
        self.null_mvt_flag = null_mvt_flag
        self.name = name
        try:
            fid = open (filename, 'r')
        except:
            print (filename + 'introuvable.')
            self.ok = False
            return
        self.contenu = fid.readlines ()
        fid.close ()
        self.hauteur = len (self.contenu)
        self.largeur = len (self.contenu [0]) - 1
        '''
        S : starting position
        G : goal
        '''
        self.pos_Goal = [-1, -1]
        self.pos_start = [x, y]
        for i in range (self.hauteur):
            for j in range (self.largeur):
                if self.contenu [i] [j] == 'S':
                    self.start = [j, i]
                    self.contenu [i] [j] == ' '
                elif self.contenu [i] [j] == 'G':
                    self.pos_Goal = [j, i]
                    self.contenu [i] [j] == ' '
        if self.pos_start == [-1, -1]:
            print ('La position initiale doit être fixée.')
            self.ok = False
            return
        self.pos = self.pos_start
        if self.pos_Goal == [-1, -1]:
            print ('La position finale doit être fixée.')
            self.ok = False
            return
        self.return_Goal = rG
        self.return_step = rs
        self.nb_steps = 0
        return

    def reset (self):
        self.pos = self.pos_start
        self.nb_steps = 0
        return self.pos

    def set_sortie (self, x, y):
        if self.contenu [y] [x] == ' ':
            self.pos_Goal = [x, y]

    def __repr__(self):
        return f"Labyrinthe {self.name}"

    def __str__(self):
        return f"Labyrinthe {self.name}"

    def __reward (self):
        if not self.ok:
            return 0
        if self.pos == self.pos_Goal:
            return self.return_Goal
        else:
            return 0

    def __done (self):
        if not self.ok:
            return False
        if self.pos == self.pos_Goal:
            return True
        else:
            return False

    def step (self, action):
        '''
        ATTENTION : contenu est indexé contenu [y] [x] !!!!

        Par contre les positions sont bien [x] [y].
        '''

        # on vérifie que l'action est valide
        if (action < 0) | (action > 4):
            return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
        # si l'action rester sur place est interdite, 0 n'est pas valide
        if (not self.null_mvt_flag) & (action == 0):
            return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
        # on vérifie que l'initialisation s'est bien passée
        if not self.ok:
            return [-1,-1], -1, False, {}
        # on vérifie que la tâche n'est pas terminée
        if self.__done ():
            return self.pos, self.__reward (), True, { 'n': self.nb_steps }

        # si tous ces tests sont passés avec succès, on va effectuer l'action
        self.nb_steps += 1
        if action == 1: # gauche
            if self.pos [0] == 0:
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
            elif self.contenu [self.pos [1]] [self. pos [0] - 1] == '*':
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
            else:
                self.pos [0] -= 1
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
        elif action == 2: # droite
            if self.pos [0] == self.largeur:
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
            elif self.contenu [self.pos [1]] [self. pos [0] + 1] == '*':
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
            else:
                self.pos [0] += 1
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
        elif action == 3: # haut
            if self.pos [1] == 0:
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
            elif self.contenu [self.pos [1] - 1] [self. pos [0]] == '*':
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
            else:
                self.pos [1] -= 1
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
        elif action == 4: # bas
            if self.pos [1] == self.hauteur:
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
            elif self.contenu [self.pos [1] + 1] [self. pos [0]] == '*':
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
            else:
                self.pos [1] += 1
                return self.pos, self.__reward (), self.__done (), { 'n': self.nb_steps }
        return self.pos, self. __reward (), self.__done (), { 'n': self.nb_steps }

    '''
    def action_space (self):
        return spaces.Discrete (5)

    def observation_space (self):
        return spaces.Box (2)
    '''
    
    def possible_actions (self):
        pa = [True, True, True, True, True]
        lpa = [0]
        if self. pos [0] == 0:
            pa [1] = False
        elif self. contenu [self. pos [1]] [self. pos [0] - 1] == '*':
            pa [1] = False
        else:
            lpa.append (1)
        if self. pos [0] == self. largeur - 1:
            pa [2] = False
        elif self. contenu [self. pos [1]] [self. pos [0] + 1] == '*':
            pa [2] = False
        else:
            lpa.append (2)
        if self. pos [1] == 0:
            pa [3] = False
        elif self. contenu [self. pos [1] - 1] [self. pos [0]] == '*':
            pa [3] = False
        else:
            lpa.append (3)
        if self. pos [1] == self. hauteur - 1:
            pa [4] = False
        elif self. contenu [self. pos [1] + 1] [self. pos [0]] == '*':
            pa [4] = False
        else:
            lpa.append (4)
        return pa, lpa
