import numpy as np
import eval_sol
import math
import numpy.ma as ma
from collections import deque
from sympy.utilities.iterables import multiset_permutations


def random(tasks):
    ind = np.arange(len(tasks))
    np.random.shuffle(ind)
    return tasks[ind]


def sort_by_exec_time(tasks):
    ind = np.argsort(tasks[:, 0])
    return ind


def sort_by_importance(tasks):
    ind = np.argsort(tasks[:, 1])
    return ind


def brute_force(tasks, last_ind=None):
    best_score = np.inf
    i = -1
    first = True
    for ind in multiset_permutations(np.arange(len(tasks))):
        i += 1
        if last_ind is not None and i < last_ind:
            continue
        else:
            if first:
                first = False
                print("Let's explore !")

        score = eval_sol.eval_solution(tasks[ind])
        best_score = min(best_score, score)
        if best_score == score:
            print("found new best score: " + str(best_score) + ", ind: " + str(i))
    return best_score


def local_search(ind, tasks, best_score):
    # taking first 8 neighbors
    for perm in multiset_permutations(ind[:8]):
        new_ind = np.append(perm, ind[8:].reshape(-1, 1))
        score = eval_sol.eval_solution(tasks[new_ind])
        if score < best_score:
            best_score = score
            print("new best score found: " + str(best_score))
            print(new_ind)
    return best_score, new_ind


def heuristique_local_search(tasks):
    ind = sort_by_importance(tasks)
    init_score = eval_sol.eval_solution(tasks[ind])
    print("init pos: " + str(ind))
    print("init score: " + str(init_score))

    best_score, new_ind = local_search(ind, tasks, init_score)
    if best_score == init_score:
        ind = new_ind

    return best_score, ind


def heuristique_hill_climbing(tasks):
    ind = sort_by_importance(tasks)
    best_score = eval_sol.eval_solution(tasks[ind])
    print("init pos: " + str(ind))
    print("init score: " + str(best_score))
    for i in range(2, len(tasks)):
        print("i: " + str(i) + ", perm: " + str(ind[:i]))
        for perm in multiset_permutations(ind[:i]):
            new_ind = np.append(perm, ind[i:].reshape(-1, 1))
            score = eval_sol.eval_solution(tasks[new_ind])
            if score < best_score:
                best_score = score
                print("new best score found: " + str(best_score))
                print(new_ind)
    return


def rot_fix(tasks, fix_indices):
    mask = np.array([True] * len(tasks))
    mask[fix_indices] = False
    tmp_tasks = tasks[mask]
    for i in range(len(tmp_tasks)):
        tmp_tasks = np.roll(tmp_tasks, 1)
        tmp_res = tmp_tasks
        for f_i in np.sort(fix_indices):
            tmp_res = np.insert(tmp_res, f_i, tasks[f_i])
        yield tmp_res


def heuristique_vnd(tasks):
    ind = np.arange(len(tasks))
    np.random.shuffle(ind)
    best_score = eval_sol.eval_solution(tasks[ind])
    print("init pos: " + str(ind))
    print("init score: " + str(best_score))

    fixed_tasks = np.array([], dtype=int)
    for t_i in range(len(tasks)):
        found = False
        fixed_tasks = np.append(fixed_tasks, t_i)  # rotate over t_i
        for tmp_ind in rot_fix(ind, fixed_tasks):
            print("fixed_tasks: " + str(fixed_tasks))
            print("tmp_ind: " + str(tmp_ind))
            score = eval_sol.eval_solution(tasks[tmp_ind])
            if score < best_score:
                best_score = score
                print("new best score found: " + str(best_score) + ", fixed_tasks: " + str(fixed_tasks))
                print("tmp_ind: " + str(tmp_ind))
                found = True
        if not found:
            fixed_tasks = fixed_tasks[:-1]  # delete last added one

    return


def heuristique_vnd_2(tasks):
    ind = np.arange(len(tasks))
    np.random.shuffle(ind)
    best_score = eval_sol.eval_solution(tasks[ind])
    print("init pos: " + str(ind))
    print("init score: " + str(best_score))

    cpt = 0
    for t_i in range(len(tasks)):
        subset = ind[t_i:t_i + 5]
        for perm in multiset_permutations(subset):
            tmp_ind = np.concatenate((ind[0:t_i], perm, ind[t_i + 6:]))
            score = eval_sol.eval_solution(tasks[tmp_ind])
            if score < best_score:
                best_score = score
                print("new best score found: " + str(best_score))
                print("tmp_ind: " + str(tmp_ind))
            cpt += 1
    print(cpt)
    return


def heuristique_ils2(tasks):
    ind = np.arange(len(tasks))
    np.random.shuffle(ind)
    best_score = eval_sol.eval_solution(tasks[ind])
    print("init pos: " + str(ind))
    print("init score: " + str(best_score))

    # take 5 nbh per grp
    cpt = 0
    nb_nbh_grps = int(len(ind) / 8)
    splits = np.split(ind, nb_nbh_grps)
    for i in range(len(splits)):
        remain_splits = splits.copy()
        explore = remain_splits.pop(i)
        for perm in multiset_permutations(explore):
            tmp_ind = np.array([], dtype=int)
            for k in range(len(splits)):
                if k == i:
                    tmp_ind = np.append(tmp_ind, perm)
                else:
                    tmp_ind = np.append(tmp_ind, splits[k])
            score = eval_sol.eval_solution(tasks[tmp_ind])
            if score < best_score:
                best_score = score
                print("new best score found: " + str(best_score) + ", in split_nb: " + str(i))
                print("tmp_ind: " + str(tmp_ind))
            cpt += 1
        print()
    print(cpt)
    return


def heuristique_ils(tasks):
    best_score, ind = heuristique_local_search(tasks)
    historique = {str(ind): best_score}
    while True:
        np.random.shuffle(ind)
        if str(ind) not in historique:
            new_score, ind = local_search(ind, tasks, best_score)
            historique[str(ind)] = best_score
            if new_score < best_score:
                best_score = new_score


def main():
    args = eval_sol.arg_parser()
    tasks = eval_sol.input_tasks(args)
    nb_tasks = len(tasks)
    nb_perm = math.factorial(nb_tasks)
    nb_perm_per_neighbor = int(nb_perm / nb_tasks)
    print("nb_tasks: %d, nb_perm: %d, nb_perm_per_neighbor: %d" % (nb_tasks, nb_perm, nb_perm_per_neighbor))
    heuristique_vnd_2(tasks)


if __name__ == "__main__":
    main()
