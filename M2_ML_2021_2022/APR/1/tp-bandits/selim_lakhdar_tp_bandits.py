import numpy as np
import bandits
import utils
import matplotlib.pyplot as plt
import time


def round_robin(bandit, horizon):
    nbr_echantillon = np.zeros(bandit.nbr_arms)
    Regret = np.zeros(horizon)

    for t in range(horizon):
        # a = utils.randamin(nbr_echantillon)
        a = t % bandit.nbr_arms
        nbr_echantillon[a] += 1
        r = bandit.regrets[a]
        Regret[t] = Regret[max(0, t - 1)] + r
    return Regret


def ucb(bandit, horizon):
    nbr_echantillon = np.zeros(bandit.nbr_arms)
    moyennes_empirique = np.zeros(bandit.nbr_arms)
    Regret = np.zeros(horizon)

    for t in range(horizon):
        #a = np.argmax(moyennes_empirique + np.sqrt(2 * np.log(t + 1) / (nbr_echantillon + 1)))
        a = np.argmax(moyennes_empirique + np.sqrt(2 * np.log(t + 1) / (nbr_echantillon + 1)))
        echantillon = bandit.pull(a)
        moyennes_empirique[a] = nbr_echantillon[a] * moyennes_empirique[a] + echantillon
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]
        r = bandit.regrets[a]
        Regret[t] = Regret[max(0, t - 1)] + r
    return Regret


def explore_then_commit(bandit, horizon, commit=300):
    nbr_echantillon = np.zeros(bandit.nbr_arms)
    Regret = np.zeros(horizon)
    exploration_gains = np.zeros(bandit.nbr_arms)

    # exploration
    for t in range(1, commit):
        # a = utils.randamin(nbr_echantillon)
        a = t % bandit.nbr_arms
        echantillon = bandit.pull(a)
        exploration_gains[a] += echantillon
        nbr_echantillon[a] += 1
        r = bandit.regrets[a]
        Regret[t] = Regret[max(0, t - 1)] + r

    # exploitation
    best_arm = np.argmax(exploration_gains)
    for t in range(commit, horizon):
        r = bandit.regrets[best_arm]
        Regret[t] = Regret[max(0, t - 1)] + r
    return Regret


def imed(bandit, horizon):
    nbr_echantillon = np.zeros(bandit.nbr_arms)
    moyennes_empirique = np.zeros(bandit.nbr_arms)
    Regret = np.zeros(horizon)

    for t in range(horizon):
        a = np.argmin(nbr_echantillon * utils.klGaussian(moyennes_empirique, np.max(moyennes_empirique)) + np.log(
            nbr_echantillon + 1))

        echantillon = bandit.pull(a)
        moyennes_empirique[a] = nbr_echantillon[a] * moyennes_empirique[a] + echantillon
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]
        r = bandit.regrets[a]
        Regret[t] = Regret[max(0, t - 1)] + r
    return Regret


def klucb(bandit, horizon):
    nbr_echantillon = np.zeros(bandit.nbr_arms)
    moyennes_empirique = np.zeros(bandit.nbr_arms)
    Regret = np.zeros(horizon)

    for t in range(horizon):
        for first in range(bandit.nbr_arms):
            I = np.zeros(bandit.nbr_arms)
            for second in range(bandit.nbr_arms):
                k = nbr_echantillon[first] * utils.klGaussian(moyennes_empirique[first], moyennes_empirique[second])
                if k < (np.log(max(1, t)) + 3 * np.log(max(1, t))):
                    if I[first] < moyennes_empirique[second]:
                        I[first] = moyennes_empirique[second]
        a = np.argmax(I)

        echantillon = bandit.pull(a)
        moyennes_empirique[a] = nbr_echantillon[a] * moyennes_empirique[a] + echantillon
        nbr_echantillon[a] += 1
        moyennes_empirique[a] = moyennes_empirique[a] / nbr_echantillon[a]
        r = bandit.regrets[a]
        Regret[t] = Regret[max(0, t - 1)] + r
    return Regret


def thompson(bandit, horizon):
    nbr_echantillon = np.zeros(bandit.nbr_arms)
    moyennes_empirique = np.zeros(bandit.nbr_arms)
    Regret = np.zeros(horizon)

    for t in range(bandit.nbr_arms):
        a = t % bandit.nbr_arms
        echantillon = bandit.pull(a)
        exploration_gains[a] += echantillon
        nbr_echantillon[a] += 1
        r = bandit.regrets[a]
        Regret[t] = Regret[max(0, t - 1)] + r

    for t in range(bandit.nbr_arms, horizon):
        tmp = np.zeros(bandit.nbr_arms)
        for b in range(bandit.nbr_arms):
            tmp[b] = rdm.betavariate(S[b], nbr_echantillon[b] - S[b] + 1)
        a = np.argmax(tmp)




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
    MEANS = np.array([0.1, 0.3, 0.4, 0.75, 0.8, 0.9, 0.95])
    normal_bandit = bandits.NormalBandit(MEANS)
    bernoulli_bandit = bandits.BernoulliBandit(MEANS)
    H = 1000
    EXP = 200

    fig, ax = plt.subplots()

    print("Processing ETC")
    start = time.time()
    r_etc, std_etc = plusieursXP(explore_then_commit, normal_bandit, H, EXP)
    end = time.time()
    plt.plot(r_etc, label="ETC")
    plt.fill_between(np.arange(H), np.maximum(0, r_etc - std_etc), r_etc + std_etc, alpha=0.3)
    print("ETC exec time: ", end - start)

    print("Processing UCB")
    start = time.time()
    r_ucb, std_ucb = plusieursXP(ucb, normal_bandit, H, EXP)
    end = time.time()
    plt.plot(r_ucb, label="UCB")
    plt.fill_between(np.arange(H), np.maximum(0, r_ucb - std_ucb), r_ucb + std_ucb, alpha=0.3)
    print("UCB exec time: ", end - start)


    print("Processing Round Robin")
    start = time.time()
    r_rr, std_rr = plusieursXP(round_robin, normal_bandit, H, EXP)
    end = time.time()
    plt.plot(r_rr, label="Round Robin")
    plt.fill_between(np.arange(H), np.maximum(0, r_rr - std_rr), r_rr + std_rr, alpha=0.3)
    print("Round Robin exec time: ", end - start)


    print("Processing IMED")
    start = time.time()
    r_imed, std_imed = plusieursXP(imed, normal_bandit, H, EXP)
    end = time.time()
    plt.plot(r_imed, label="IMED")
    plt.fill_between(np.arange(H), np.maximum(0, r_imed - std_imed), r_imed + std_imed, alpha=0.3)
    print("IMED exec time: ", end - start)

    print("Processing KLUCB")
    start = time.time()
    r_klucb, std_klucb = plusieursXP(klucb, normal_bandit, H, EXP)
    end = time.time()
    plt.plot(r_klucb, label="KLUCB")
    plt.fill_between(np.arange(H), np.maximum(0, r_klucb - std_klucb), r_klucb + std_klucb, alpha=0.3)
    print("KLUCB exec time: ", end - start)

    plt.title(f"Regret - Horizon = {H}, Nombre d'XPs = {EXP}")
    plt.legend()
    plt.show()

    fig.savefig("rr_ucb_imed_klucb_regret.png")
