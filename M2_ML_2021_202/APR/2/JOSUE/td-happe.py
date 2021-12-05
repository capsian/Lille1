import labyrinthe
import matplotlib.pyplot as plt
import numpy as np
lab = labyrinthe.Labyrinthe(filename = 'laby.1', x=1, y=1)
lab.reset()
gamma = 0.9
NB_EPISODES=50
N = 100 #nb d'expériences
#La fonction raandamax du fichier utils.py du dernier TP
def randamax(V, T=None, I=None):
    """
    V: array of values
    T: array used to break ties
    I: array of indices from which we should return an amax
    """
    if I is None:
        idxs = np.where(V == np.amax(V))[0]
        if T is None:
            idx = np.random.choice(idxs)
        else:
            assert len(V) == len(T), f"Lengths should match: len(V)={len(V)} - len(T)={len(T)}"
            t_idxs = np.where(T[idxs] == np.amin(T[idxs]))[0]
            t_idxs = np.random.choice(t_idxs)
            idx = idxs[t_idxs]
    else:
        idxs = np.where(V[I] == np.amax(V[I]))[0]
        if T is None:
            idx = I[np.random.choice(idxs)]
        else:
            assert len(V) == len(T), f"Lengths should match: len(V)={len(V)} - len(T)={len(T)}"
            t = T[I]
            t_idxs = np.where(t[idxs] == np.amin(t[idxs]))[0]
            t_idxs = np.random.choice(t_idxs)
            idx = I[idxs[t_idxs]]
    return idx


def q_learning(fpath,gamma,start_x=1,start_y=1):
    #On instantie notre labyrinthe
    laby = labyrinthe.Labyrinthe(filename = fpath, x=start_x, y=start_y)
    #qsa[s][a] = Q(s,a)
    qsa = np.zeros((laby.largeur*laby.hauteur,5))
    #nsa[s][a] est égal au nombre de fois où l'action a a été effectuée en l'état s
    nsa = np.zeros((laby.hauteur*laby.largeur,5))
    nb_step = np.zeros(NB_EPISODES)
    epsilon = 1
    for i in range(NB_EPISODES):
        laby.reset()
        t=0
        ep_termine = False
        while(not ep_termine):
            state = laby.largeur*laby.pos[1]+laby.pos[0]
            #On applique l'algo glouton avec un epsilon décroissant pour choisir l'action
            k = np.random.rand()
            if (k<epsilon):
                action = np.random.randint(5)
                #a = np.random.randint(len(laby.possible_actions()[1]))
                #action = laby.possible_actions()[1][a]
            else:
                action = randamax(qsa[state])
            observ = laby.step(action)
            new_state = laby.largeur*laby.pos[1]+laby.pos[0]
            #On update Q(s,a)
            qsa[state][action] = qsa[state][action] + 1/(nsa[state][action]+1)*(observ[1]+gamma*max(qsa[new_state])-qsa[state][action])
            nsa[state][action]+=1
            t+=1
            ep_termine = observ[2]
        epsilon*=0.9
        nb_step[i]=t
    return nb_step

fig, ax = plt.subplots()
ax.xaxis.set_label_text('Nombre d\'épisodes')
ax.yaxis.set_label_text('Nombre de pas')
ax.set_title("Q1 - gamma = 0.9")
ax.plot(q_learning('laby.1',0.9))
fig.savefig("q1.png")
fig.clf()

Pas = np.zeros((N,NB_EPISODES))
Pas_05 = np.zeros((N,NB_EPISODES))
Pas_01 = np.zeros((N,NB_EPISODES))

for i in range(N):
    if (i%10==9):
        print("XP "+str(i+1)+"/100")
    Pas[i] = q_learning('laby.1',0.9)
    Pas_05[i] = q_learning('laby.1',0.5)
    Pas_01[i] = q_learning('laby.1',0.1)
Pas_moyen = np.mean(Pas, axis=0)
Pas_moyen_05 = np.mean(Pas_05, axis=0)
Pas_moyen_01 = np.mean(Pas_01, axis=0)
fig, ax = plt.subplots()
ax.xaxis.set_label_text('Nombre d\'épisodes')
ax.yaxis.set_label_text('Nombre de pas')
ax.set_title("Moyenne pour 100 expériences")
ax.plot(Pas_moyen,c='b',label="gamma=0.9")
fig.legend()
fig.savefig("q2.png")
ax.plot(Pas_moyen_05,c='g',label="gamma=0.5")
ax.plot(Pas_moyen_01,c='r',label="gamma=0.1")
fig.legend(loc="upper right")
fig.savefig("q3.png")
