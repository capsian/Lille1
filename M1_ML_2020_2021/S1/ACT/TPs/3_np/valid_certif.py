import numpy as np

# nb machines
m = int(input())
# nb tasks
n = int(input())

tasks = []
for i in range(n):
    t_begin, t_end = input().split(" ")
    tasks += [[int(t_begin), int(t_end)]]

# max wait
d = int(input())

print(tasks)
print("d: " + str(d))


# certif: [task_pos ...]
def valid_certif(certif):
    # represent the remain time of task exec on each machine
    machines_exec_time = [0] * m
    last_curr_time, curr_time = 0, 0

    # update time and return pos if a machine is available
    def update_machines_exec_time(elp_time):
        print("update_machines_exec_time: " + str(elp_time) + ", machines_exec_time: " + str(machines_exec_time),
              end="")
        pos = -1
        for t in range(len(machines_exec_time)):
            if elp_time >= machines_exec_time[t]:
                pos = t
                machines_exec_time[t] = 0
            else:
                machines_exec_time[t] -= elp_time
        print(", machines_exec_time2: " + str(machines_exec_time) + ", pos: " + str(pos))
        return pos

    for _ in range(len(certif)):

        # take the task that begins the first
        task_pos = int(np.argmin(certif))
        curr_time = tasks[task_pos][0]

        print("task_pos: " + str(task_pos) + ", curr_time: " + str(curr_time))

        # check if the task is lunched after submit time
        if tasks[task_pos][0] < curr_time:
            print(
                "check if the task is lunched after submit time .... failed: " + str(tasks[task_pos][0]) + " < " + str(
                    curr_time))
            return False

        # check if task is lunched before max wait d
        if tasks[task_pos][0] - curr_time > d:
            print("check if task is lunched before max wait d.... failed: " + str(tasks[task_pos][0]) + " - " + str(
                curr_time) + " > " + str(d))
            return False

        elapsed_time = abs(curr_time - last_curr_time)
        m_pos = update_machines_exec_time(elapsed_time)
        if m_pos == -1:
            for _ in range(0, d):
                print("wait 1 sec ...")
                curr_time += 1
                m_pos = update_machines_exec_time(i)
                if m_pos != -1:
                    break
            if m_pos == -1:
                print("No more machines !!!")
                return False

        machines_exec_time[m_pos] = tasks[task_pos][1]
        last_curr_time = curr_time

        # del task
        certif[task_pos] = np.inf

    return True


CERTIF_DONNE0 = [
    2,
    0,
    4,
    3,
    1
]

CERTIF_DONNE1 = [
    2,
    0,
    4,
    3,
    1
]

CERTIF_DONNE2 = [
    3,
    0,
    4,
    2,
    1
]

print("====")
print("CERTIF_DONNE0: " + str(CERTIF_DONNE0))
print("CERTIF_DONNE1: " + str(CERTIF_DONNE1))
print("CERTIF_DONNE2: " + str(CERTIF_DONNE2))
print("====")

print(valid_certif(CERTIF_DONNE2))
