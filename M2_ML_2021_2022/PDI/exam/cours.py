import numpy as np

N = 3  # nb of states
M = 3  # nb of actions
P = np.array([[[1 / 2, 1 / 4, 1 / 4],
               [1 / 16, 3 / 4, 3 / 16],
               [1 / 4, 1 / 8, 5 / 8]],
              [[1 / 2, 0, 1 / 2],
               [0, 0, 0],
               [1 / 16, 7 / 8, 1 / 16]],
              [[1 / 4, 1 / 4, 1 / 2],
               [1 / 8, 3 / 4, 1 / 8],
               [3 / 4, 1 / 16, 3 / 16]]])
R = np.array([10, 4, 8, 8, 2, 4, 4, 6, 4, 14, 0, 18, 0, 0, 0, 8, 16, 8,
              10, 2, 8, 6, 4, 2, 4, 0, 8])
R = R.reshape([N, M, N])
Policy = np.array([
    [1 / 3, 1 / 3, 1 / 3],
    [1 / 2, 0, 1 / 2],
    [1 / 3, 1 / 3, 1 / 3]
])

GAMMA = 0.9
S = list(range(N))
A = list(range(M))


def compute_value(S, A, P, R, politique, gamma):
    alpha = np.zeros((N, N))
    beta = np.zeros(N)

    for i in range(N):
        si = S[i]
        for j in range(N):
            sj = S[j]
            if i != j:
                alpha[i, j] = - gamma * sum(politique[si, a] * P[si, a, sj] for a in A)
            else:
                alpha[i, j] = 1 - gamma * sum(politique[si, a] * P[si, a, sj] for a in A)

        beta[i] = sum(politique[si, a] * sum(P[si, a, s_] * R[si, a, s_] for s_ in S) for a in A)
    V = np.linalg.solve(alpha, beta)
    return V


print(compute_value(S, A, P, R, Policy, GAMMA), "\n")


def opt_bellman(S, A, P, R, politique, gamma):
    alpha = np.zeros((N, N))
    beta = np.zeros(N)

    for i in range(N):
        si = S[i]
        for j in range(N):
            sj = S[j]

            alpha[i, j] = sum(politique[si, a] * P[si, a, sj] for a in A)

        beta[i] = sum(politique[si, a] * sum(P[si, a, s_] * R[si, a, s_] for s_ in S) for a in A)
    v_pi = np.zeros(N)
    v_pi_old = np.zeros(N)
    delta_inf = np.zeros(10000)
    stop = False
    i = 0
    while (not stop) and (i < 10000):
        v_pi = beta + GAMMA * (alpha @ v_pi_old)
        delta_inf[i] = np.max(np.abs(v_pi - v_pi_old))
        v_pi_old[:] = v_pi
        if delta_inf[i] < 1e-4:
            stop = True
            delta_inf = delta_inf[:i + 1]
        i += 1
    return v_pi


print(opt_bellman(S, A, P, R, Policy, GAMMA))


def policy_improvement(v):
    Q = np.zeros((N, M))
    for state in range(N):
        for action in range(M):
            transitions_info = P[state][action]
            for transition in transitions_info:
                probabilities = transition[0]
                next_state = transition[1]
                reward = transition[2]
                Q[state, action] += probabilities * (reward + GAMMA * v[next_state])
    # Compute the/a greedy policy with respect to the Q/V value function
    pi = np.argmax(Q, axis=1)
    return pi



def policy_iter(max_iter):
    pi = np.zeros(N)
    stop = False
    i = 0
    while (not stop) and (i < max_iter):
        pi_old = np.copy(pi)

        # policy evaluation
        # v_pi = value_function(pi)  # test value_function_2 too !
        v_pi = opt_bellman(S, A, P, R, pi, GAMMA)

        # policy improvement
        pi = policy_improvement(v_pi)

        i += 1
        stop = np.array_equal(pi, pi_old)

    return pi


print(policy_iter(1000))
