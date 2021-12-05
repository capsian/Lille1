import numpy as np
import random
import matplotlib.pyplot as plt

import bandits

random.seed(42)

bernoulli_distrib = [0.1, 0.3, 0.4, 0.75, 0.8, 0.9, 0.95]
gaussian_distrib = [0.1, 0.3, 0.4, 0.75, 0.8, 0.9, 0.95]

ber_b = bandits.BernoulliBandit(np.array(bernoulli_distrib))
gaus_b = bandits.NormalBandit(np.array(gaussian_distrib))


def round_robin(b, horizon=1000):
    gains = []
    regrets = []
    for i in range(horizon):
        a = i % b.nbr_arms
        gains += [b.pull(a)]
        regrets += [b.regrets[a]]

    return gains, regrets


def explore_then_commit(b, horizon=1000, commit=300):
    explore_gains_hist = np.zeros((horizon, b.nbr_arms), dtype=float)
    explore_regrets_hist = np.zeros((horizon, b.nbr_arms), dtype=float)

    explore_gains = np.zeros(b.nbr_arms)
    explore_regrets = np.zeros(b.nbr_arms)
    for i in range(commit):
        for a in range(b.nbr_arms):
            g = b.pull(a)
            r = b.regrets[a]
            explore_gains[a] += g
            explore_regrets[a] += r
            explore_gains_hist[i, a] = g
            explore_regrets_hist[i, a] = r
            #print(g, explore_gains_hist[i, a], r, explore_regrets_hist[i, a])

    # take arm with max profit
    best_arm = np.argmax(explore_gains)

    exploit_gains = []
    exploit_regrets = []
    for i in range(horizon - commit):
        g = b.pull(best_arm)
        r = b.regrets[best_arm]
        exploit_gains += [g]
        exploit_regrets += [r]
        explore_gains_hist[i, best_arm] = g
        explore_regrets_hist[i, best_arm] = r
        #print(g, explore_gains_hist[i, best_arm], r, explore_regrets_hist[i, a])

    return explore_gains_hist[:, best_arm], explore_regrets_hist[:, best_arm]


def bandit_experiment(model, b, horizon=1000, N=200):
    all_gains = np.zeros((N, horizon))
    all_regrets = np.zeros((N, horizon))

    for i in range(N):
        gains, regrets = model(b, horizon=horizon)
        all_gains[i] = np.array(gains)
        all_regrets[i] = np.array(regrets)

    r_mean = np.mean(all_regrets, axis=0)
    r_std = np.std(all_regrets, axis=0)

    return r_mean, r_std



# rr_gains, rr_regret = round_robin(ber_b)
# fig, ax = plt.subplots()
# ax.set_title('round_robin gains vs reget')
# ax.xaxis.set_label_text('n')
# ax.yaxis.set_label_text('cumsum(gains) / cumsum(regret)')
# ax.plot(range(1000), np.cumsum(rr_gains), color='red', alpha=0.2, label="gains")
# ax.plot(range(1000), np.cumsum(rr_regret), color='blue', alpha=0.2, label="regret")
# ax.legend()
# fig.savefig("round_robin_bernoulli_gain_regret.png")
#
# gau_gains, gau_regret = round_robin(gaus_b)
# fig, ax = plt.subplots()
# ax.set_title('round_robin gains vs reget')
# ax.xaxis.set_label_text('n')
# ax.yaxis.set_label_text('cumsum(gains) / cumsum(regret)')
# ax.plot(range(1000), np.cumsum(gau_gains), color='red', alpha=0.2, label="gains")
# ax.plot(range(1000), np.cumsum(gau_regret), color='blue', alpha=0.2, label="regret")
# ax.legend()
# fig.savefig("round_robin_gaussian_gain_regret.png")


# gain, regret = explore_then_commit(ber_b)
# fig, ax = plt.subplots()
# ax.set_title('round_robin gains vs reget')
# ax.xaxis.set_label_text('n')
# ax.yaxis.set_label_text('cumsum(gains) / cumsum(regret)')
# ax.plot(np.arange(len(gain)), np.cumsum(gain), color='red', alpha=0.2, label="gains")
# ax.plot(np.arange(len(regret)), np.cumsum(regret), color='blue', alpha=0.2, label="regret")
# ax.legend()
# fig.savefig("explore_then_commit_gain_regret.png")


r_mean, r_std = bandit_experiment(explore_then_commit, ber_b)
fig, ax = plt.subplots()
ax.set_title('bandit experiment explore then commit')
ax.xaxis.set_label_text('horizon')
ax.yaxis.set_label_text('cumsum(gains) / cumsum(regret)')
ax.plot(np.arange(len(r_mean)), np.cumsum(r_mean), color='red', alpha=0.2, label="mean regret")
ax.legend()
fig.savefig("exp_explore_then_commit.png")
