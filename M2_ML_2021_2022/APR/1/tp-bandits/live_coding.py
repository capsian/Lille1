import numpy as np
import bandits
import utils
import matplotlib.pyplot as plt


def round_robin(bandit, horizon):
    nbr_echantillon = np.zeros(bandit.nbr_arms)
    Regret = np.zeros(horizon)

    for t in range(horizon):
        a = utils.randamin(nbr_echantillon)
        nbr_echantillon[a] += 1
        r = bandit.regrets[a]
        Regret[t] = Regret[max(0, t-1)] + r
    return Regret


def ucb(bandit, horizon):
    nbr_echantillon = np.zeros(bandit.nbr_arms)
    moyennes_empirique = np.zeros(bandit.nbr_arms)
    Regret = np.zeros(horizon)

    for t in range(horizon):
        a = utils.randamax(moyennes_empirique + np.sqrt(2 * np.log(t+1) / (nbr_echantillon + 1)))
        echantillon = bandit.pull(a)
        moyennes_empirique[a] = nbr_echantillon[a] * moyennes_empirique[a] + echantillon
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]
        r = bandit.regrets[a]
        Regret[t] = Regret[max(0, t-1)] + r
    return Regret


def plusieursXP(algo, bandit, horizon, N):
    Regrets = np.zeros((N, horizon))
    for exp in range(N):
        R = algo(bandit, horizon)
        Regrets[exp] = R
    Regret_moyen = np.mean(Regrets, axis=0)
    Regret_std = np.std(Regrets, axis=0)
    return Regret_moyen, Regret_std


if __name__ == "__main__":
    np.random.seed(12345)
    MEANS = np.array([0.1, 0.2, 0.9])
    normal_bandit = bandits.NormalBandit(MEANS)
    bernoulli_bandit = bandits.BernoulliBandit(MEANS)
    H = 1000
    EXP = 200

    r_ucb, std_ucb = plusieursXP(ucb, normal_bandit, H, EXP)
    plt.plot(r_ucb, label="UCB")
    plt.fill_between(np.arange(H), np.maximum(0, r_ucb - std_ucb), r_ucb + std_ucb, alpha=0.3)

    r_rr, std_rr = plusieursXP(round_robin, normal_bandit, H, EXP)
    plt.plot(r_rr, label="Round Robin")
    plt.fill_between(np.arange(H), np.maximum(0, r_rr - std_rr), r_rr + std_rr, alpha=0.3)

    plt.title(f"Regret - Horizon = {H}, Nombre d'XPs = {EXP}")
    plt.legend()
    plt.show()