import numpy as np
import random
import matplotlib.pyplot as plt

import bandits

random.seed(42)

def baseline(bandit, horizon=1000):
    rewards = []
    regrets = []
    for i in range(horizon):
        a = random.randint(0, b.nbr_arms-1)
        reward = b.pull(a)
        rewards += [reward]
        if a != b.best_arm:
            regrets += [1]
        else:
            regrets += [0]

    return rewards, regrets

def eps_greedy(bandit, eps=1, horizon=1000):
    rewards = []
    regrets = []
    means = [.0] * bandit.nbr_arms
    nb_pulls = [0] * bandit.nbr_arms

    # init: pull each arm once
    for a in range(bandit.nbr_arms):
        reward = bandit.pull(a)
        rewards += [reward]
        if a != bandit.best_arm:
            regrets += [1]
        else:
            regrets += [0]

        means[a] = nb_pulls[a] * means[a] + reward
        nb_pulls[a] += 1
        means[a] = means[a] / nb_pulls[a]

    # greedy
    for t in range(bandit.nbr_arms, horizon):
        p = np.random.rand()
        if p < eps:
            a = np.random.randint(bandit.nbr_arms)
        else:
            a = np.argmax(means)


        regret = 1 if a == bandit.best_arm else 0
        reward = bandit.pull(a)

        rewards += [reward]
        regrets += [regret]

        means[a] = nb_pulls[a] * means[a] + reward
        nb_pulls[a] += 1
        means[a] = means[a] / nb_pulls[a]

    return rewards, regrets


def eps_greedy_desc(bandit, eps=1, horizon=1000):
    rewards = []
    regrets = []
    means = [.0] * bandit.nbr_arms
    nb_pulls = [0] * bandit.nbr_arms

    # init: pull each arm once
    for a in range(bandit.nbr_arms):
        reward = bandit.pull(a)
        rewards += [reward]
        if a != bandit.best_arm:
            regrets += [1]
        else:
            regrets += [0]

        means[a] = nb_pulls[a] * means[a] + reward
        nb_pulls[a] += 1
        means[a] = means[a] / nb_pulls[a]

    # greedy
    for t in range(bandit.nbr_arms, horizon):
        p = np.random.rand()
        if p < eps:
            a = np.random.randint(bandit.nbr_arms)
        else:
            a = np.argmax(means / (t+bandit.nbr_arms))


        regret = 1 if a == bandit.best_arm else 0
        reward = bandits.pull(a)

        rewards += [reward]
        regrets += [regret]

        means[a] = nb_pulls[a] * means[a] + reward
        nb_pulls[a] += 1
        means[a] = means[a] / nb_pulls[a]

        eps *= .99

    return rewards, regrets


def experiment(algo, bandit, horizon, N, eps=None):
    Regrets = np.zeros((N, horizon))

    for exp in range(N):

        if eps is None:
            _, R = algo(bandit, horizon=horizon)
        else:
            _, R = algo(bandit, eps=eps, horizon=horizon)

        Regrets[exp] = R

    Regret_moyen = np.mean(Regrets, axis=0)
    Regret_std = np.std(Regrets, axis=0)

    return Regret_moyen, Regret_std


if __name__ == "__main__":
    np.random.seed(12345)

    MEANS = np.array([0.3, 0.42, 0.4])
    b = bandits.BernoulliBandit(MEANS)

    H = 1000
    EXP = 200

    r_baseline, std_baseline = experiment(baseline, b, H, EXP)
    plt.plot(np.arange(H), np.cumsum(r_baseline), label="baseline")
    #plt.fill_between(np.arange(H), np.maximum(0, r_baseline - std_baseline), r_baseline + std_baseline, alpha=0.3)

    r_eps_g, std_eps_g = experiment(eps_greedy, b, H, EXP, eps=1)
    plt.plot(np.arange(H), np.cumsum(r_eps_g), label="Epsilon Greedy: 1")
    #plt.fill_between(np.arange(H), np.maximum(0, r_eps_g - std_eps_g), r_eps_g + std_eps_g, alpha=0.3)

    r_eps_g, std_eps_g = experiment(eps_greedy, b, H, EXP, eps=.5)
    plt.plot(np.arange(H), np.cumsum(r_eps_g), label="Epsilon Greedy: 0.5")

    r_eps_g, std_eps_g = experiment(eps_greedy, b, H, EXP, eps=.2)
    plt.plot(np.arange(H), np.cumsum(r_eps_g), label="Epsilon Greedy: 0.2")

    r_eps_g, std_eps_g = experiment(eps_greedy, b, H, EXP, eps=.8)
    plt.plot(np.arange(H), np.cumsum(r_eps_g), label="Epsilon Greedy: 0.8")

    plt.title(f"Regret - Horizon = {H}, Nombre d'XPs = {EXP}")
    plt.legend()
    plt.show()
