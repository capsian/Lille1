import argparse
import numpy as np


def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-it", "--input_tasks", type=str, help="input tasks file", required=True)
    args = parser.parse_args()
    return args


def input_tasks(args):
    tasks = np.array((), dtype=int)
    with open(args.input_tasks, "r") as reader:
        for l in reader.readlines():
            l = l.strip().split(" ")
            tasks = np.append(tasks, [int(l[0]), int(l[1]), int(l[2])])
    tasks = tasks.reshape(-1, 3)
    return tasks


def eval_solution(tasks):
    score = 0
    curr_time = 0
    for t in tasks:  # task[0]: task duration, task[1]: importance, task[2]: max wait
        curr_time += t[0]
        wait = max(curr_time - t[2], 0)
        score += wait * t[1]
    return score


def main():
    args = arg_parser()
    tasks = input_tasks(args)
    print("tasks:")
    print(tasks)
    print("score: " + str(eval_solution(tasks)))


if __name__ == "__main__":
    main()
