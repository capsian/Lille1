import bandits
import utils
import numpy as np
import matplotlib.pyplot as plt
import numpy as np
import random as rdm

HORIZON = 10000


def aleatoire(b, horizon):
    regrets = []
    rewards = []

    for i in range(horizon):
        arm = np.random.randint(b.nbr_arms)
        # cumulative regrets
        if len(regrets) != 0:
            regrets.append(regrets[-1] + b.regrets[arm])
        else:
            regrets.append(b.regrets[arm])

        # cumulative rewards
        if len(rewards) != 0:
            rewards.append(rewards[-1] + b.pull(arm))
        else:
            rewards.append(b.pull(arm))
    return regrets, rewards


def aleatoire_1(bandit, horizon):
    Regret = np.zeros(horizon)
    Reward = np.zeros(horizon)

    for t in range(bandit.nbr_arms, horizon):
        a = np.random.randint(bandit.nbr_arms)
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        Regret[t] = Regret[max(0, t-1)] + r
        Reward[t] = Reward[max(0, t-1)] + reward

    return Regret, Reward

#Dans la suite on decide de tirer tout les bras une fois, puis d'appliquer chacune des methodes

def eps_glouton(bandit, horizon, eps):
    Rewards = np.zeros(horizon)
    Regrets = np.zeros(horizon)
    moyennes_empirique = np.zeros(bandit.nbr_arms)
    nbr_echantillon = np.zeros(bandit.nbr_arms)

    for a in range(bandit.nbr_arms):
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        Regrets[a] = Regrets[max(0, a-1)] + r
        Rewards[a] = Rewards[max(0, a-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]

    for t in range(bandit.nbr_arms, horizon):
        p = np.random.rand()
        # partie exploration
        if p < eps:
            a = np.random.randint(bandit.nbr_arms)
        # sinon amelioration
        else:
            a = np.argmax(moyennes_empirique)
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        Regrets[t] = Regrets[max(0, t-1)] + r
        Rewards[t] = Rewards[max(0, t-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]

    return Regrets, Rewards


def eps_glouton_dec(bandit, horizon, eps):
    moyennes_empirique = np.zeros(bandit.nbr_arms)
    Rewards = np.zeros(horizon)
    Regrets = np.zeros(horizon)
    nbr_echantillon = np.zeros(bandit.nbr_arms)
    for a in range(bandit.nbr_arms):
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        Regrets[a] = Regrets[max(0, a-1)] + r
        Rewards[a] = Rewards[max(0, a-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]

    for t in range(bandit.nbr_arms, horizon):
        p = np.random.uniform(0, 1, 1)
        # partie exploration
        if p < eps:
            a = np.random.randint(bandit.nbr_arms)
        # sinon amelioration
        else:
            a = np.argmax(np.divide(moyennes_empirique))
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        Regrets[t] = Regrets[max(0, t-1)] + r
        Rewards[t] = Rewards[max(0, t-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]
        eps *= 0.999
    return Regrets, Rewards


def proportionnelle(bandit, horizon):
    Rewards = np.zeros(horizon)
    Regrets = np.zeros(horizon)
    moyennes_empirique = np.zeros(bandit.nbr_arms)
    nbr_echantillon = np.zeros(bandit.nbr_arms)
    for a in range(bandit.nbr_arms):
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        Regrets[a] = Regrets[max(0, a-1)] + r
        Rewards[a] = Rewards[max(0, a-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]

    for t in range(bandit.nbr_arms, horizon):
        a = rdm.choices(np.arange(bandit.nbr_arms), moyennes_empirique)[0]
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        Regrets[t] = Regrets[max(0, t-1)] + r
        Rewards[t] = Rewards[max(0, t-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]
    return Regrets, Rewards


def boltzmann(bandit, horizon, tau):
    Rewards = np.zeros(horizon)
    Regrets = np.zeros(horizon)
    moyennes_empirique = np.zeros(bandit.nbr_arms)

    nbr_echantillon = np.zeros(bandit.nbr_arms)
    for a in range(bandit.nbr_arms):
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        Regrets[a] = Regrets[max(0, a-1)] + r
        Rewards[a] = Rewards[max(0, a-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]

    for t in range(bandit.nbr_arms, horizon):
        a = rdm.choices(np.arange(bandit.nbr_arms), np.exp(
            moyennes_empirique / tau) / np.sum(np.exp(moyennes_empirique / tau)))[0]
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        Regrets[t] = Regrets[max(0, t-1)] + r
        Rewards[t] = Rewards[max(0, t-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]

    return Regrets, Rewards


def ucb(bandit, horizon, alpha):
    nbr_echantillon = np.zeros(bandit.nbr_arms)
    moyennes_empirique = np.zeros(bandit.nbr_arms)
    Regrets = np.zeros(horizon)
    Rewards = np.zeros(horizon)

    for a in range(bandit.nbr_arms):
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        Regrets[a] = Regrets[max(0, a-1)] + r
        Rewards[a] = Rewards[max(0, a-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]

    for t in range(bandit.nbr_arms, horizon):
        a = utils.randamax(moyennes_empirique +
                           np.sqrt(alpha * np.log(t) / (nbr_echantillon)))
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        Regrets[t] = Regrets[max(0, t-1)] + r
        Rewards[t] = Rewards[max(0, t-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]

    return Regrets, Rewards


def thompson(bandit, horizon):
    nbr_echantillon = np.ones(bandit.nbr_arms)
    moyennes_empirique = np.zeros(bandit.nbr_arms)
    S = np.ones(bandit.nbr_arms)
    Regrets = np.zeros(horizon)
    Rewards = np.zeros(horizon)

    for a in range(bandit.nbr_arms):
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        S[a] += reward
        Regrets[a] = Regrets[max(0, a-1)] + r
        Rewards[a] = Rewards[max(0, a-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]

    for t in range(bandit.nbr_arms, horizon):
        tmp = np.zeros(bandit.nbr_arms)
        for b in range(bandit.nbr_arms):
            tmp[b] = rdm.betavariate(S[b], nbr_echantillon[b] - S[b] + 1)
        a = np.argmax(tmp)
        if a == bandit.best_arm:
            r = 0
        else:
            r = 1
        reward = bandit.pull(a)
        S[a] += reward
        Regrets[t] = Regrets[max(0, t-1)] + r
        Rewards[t] = Rewards[max(0, t-1)] + reward
        moyennes_empirique[a] = nbr_echantillon[a] * \
            moyennes_empirique[a] + reward
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]

    return Regrets, Rewards


def plusieursXP(algo, bandit, horizon, N, eps=None, tau=None, alpha=None):
    Regrets = np.zeros((N, horizon))
    Rewards = np.zeros((N, horizon))
    for exp in range(N):
        if algo == eps_glouton or algo == eps_glouton_dec:
            R, REW = algo(bandit, horizon, eps)
        elif algo == boltzmann:
            R, REW = algo(bandit, horizon, tau)
        elif algo == ucb:
            R, REW = algo(bandit, horizon, alpha)
        else:
            R, REW = algo(bandit, horizon)
        Regrets[exp] = R
        Rewards[exp] = REW
    Regret_moyen = np.mean(Regrets, axis=0)
    Regret_std = np.std(Regrets, axis=0)
    return Regret_moyen, Regret_std, REW, Regrets, Rewards


def plot(b, algo, horizon, exp, lab, param=None):
    if algo == eps_glouton or algo == eps_glouton_dec:
        r, std, rew, regrets, rewards = plusieursXP(
            algo, b, horizon, exp, eps=param)
    elif algo == boltzmann:
        r, std, rew, regrets, rewards = plusieursXP(
            algo, b, horizon, exp, tau=param)
    elif algo == ucb:
        r, std, rew, regrets, rewards = plusieursXP(
            algo, b, horizon, exp, alpha=param)
    else:
        r, std, rew, regrets, rewards = plusieursXP(algo, b, horizon, exp)

    plt.plot(r, label=lab)
    plt.fill_between(np.arange(horizon), np.maximum(
        0, r - std), r + std, alpha=0.3)


if __name__ == "__main__":
    np.random.seed(1234)
    b = bandits.BernoulliBandit(np.array([0.3, 0.42, 0.4]))
    EXP = 100
    H = 10000

    # ploting results of regrets according to each method
    plot(b, aleatoire_1, H, EXP, "Regret_aleatoire")
    plot(b, eps_glouton, H, EXP, "Regret_gloutonne", 0.5)
    plot(b, proportionnelle, H, EXP, "Regret_proportionnelle")
    plot(b, boltzmann, H, EXP, "Regret_boltzmann", 1)
    plot(b, ucb, H, EXP, "Regret_ucb", 1)
    plot(b, thompson, H, EXP, "Regret_thompson")
    plt.title(f"Regret - Horizon = {HORIZON}, Nombre d'XPs = {EXP}")
    plt.legend()

    fig, axs = plt.subplots(3)
    epsilons = [0.1, 0.5, 0.85]
    fig.suptitle('Regret Glouton eps in {0.1,0.5,0.85}')
    for i in range(len(epsilons)):
        r, std, rew, regrets, rewards = plusieursXP(
            eps_glouton, b, HORIZON, EXP, eps=epsilons[i])
        axs[i].plot(r)

    fig1, ax1 = plt.subplots()
    fig1.suptitle('Regret/Reward Random Method')
    r, std, rew, regrets, rewards = plusieursXP(aleatoire_1, b, 1000, EXP)
    ax1.plot(r, label="Regret_aleatoire")
    ax1.plot(rew, label="Reward_aleatoire")
    plt.fill_between(np.arange(1000), np.maximum(
        0, r - std), r + std, alpha=0.3)

    fig2, ax2 = plt.subplots()
    fig2.suptitle('Regrets/Rewards  Horizon = 1000, Nombre XPs = 100"')
    for i in range(len(regrets)):
        ax2.plot(regrets[i])
        ax2.plot(rewards[i])

    fig3, ax3 = plt.subplots(3)
    taus = [1000, 1, 0.001]
    fig3.suptitle('Regret Boltzman tau in {1000,1,0.001}')
    for i in range(len(taus)):
        r, std, rew, regrets, rewards = plusieursXP(
            boltzmann, b, HORIZON, EXP, tau=taus[i])
        ax3[i].plot(r)

    fig4, ax4 = plt.subplots(3)
    alphas = [0.5, 1, 2]
    fig4.suptitle('Regret UCB alpha in {0.5,1,2}')
    for i in range(len(alphas)):
        r, std, rew, regrets, rewards = plusieursXP(
            ucb, b, HORIZON, EXP, alpha=alphas[i])
        ax4[i].plot(r)

    plt.show()
