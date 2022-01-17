from collections import defaultdict

from mesa.time import RandomActivation

from agents import Worker, Box, manhattan_dist


class Negotiation1(RandomActivation):

    def __init__(self, model):
        super().__init__(model)
        self.init = True
        self.agents_dict = defaultdict(dict)
        self.global_makespan = 0
        self.msg = "schedule:nego1>"

    def add(self, agent):
        """
        Add an Agent object to the schedule
        Args:
            agent: An Agent to be added to the schedule.
        """

        self._agents[agent.unique_id] = agent
        agent_class = type(agent)
        self.agents_dict[agent_class][agent.unique_id] = agent

    def remove(self, agent):
        """
        Remove all instances of a given agent from the schedule.
        """

        del self._agents[agent.unique_id]

        agent_class = type(agent)
        del self.agents_dict[agent_class][agent.unique_id]

    def get_agents_by_class(self, agent_class):
        return self.agents_dict[agent_class].values()

    def greedy_init(self):
        # initial greedy strategy: associate nearest object to each worker, by weights
        boxes_by_weight_desc = sorted(list(self.get_agents_by_class(Box)), key=lambda x: x.weight,
                                      reverse=True)
        workers_by_capacity_desc = sorted(list(self.get_agents_by_class(Worker)), key=lambda x: x.capacity,
                                          reverse=True)

        for w in workers_by_capacity_desc:
            for b in boxes_by_weight_desc:
                if w.capacity >= b.weight and b.targeted_by is None and w.target_box is None:
                    w.target_box = b
                    w.color = b.color
                    b.targeted_by = w
                    w.update_makespan()
                    print("greedy_init: worker", w.unique_id, "targeted box:", b.unique_id, 'makespan:', w.makespan)

    def recalculate_makespan(self, worker_1, worker_2):
        # worker is already carrying a box to dest
        if worker_2.carry:
            # go to worker then dist
            new_makespan = manhattan_dist(worker_1.pos, worker_2.pos)
            new_makespan += manhattan_dist(worker_2.pos, worker_2.dest_pos)
        # not carrying
        else:
            # go to box direct
            new_makespan = manhattan_dist(worker_1.pos, worker_2.target_box.pos)
            new_makespan += manhattan_dist(worker_2.target_box.pos, worker_2.dest_pos)

        return new_makespan

    def switch_box(self, w1, w2):
        tmp = w1.target_box

        w1.target_box = w2.target_box
        w1.carry = False
        w1.color = w2.target_box.color
        w1.update_makespan()

        w2.target_box = tmp
        w2.carry = False
        w2.color = tmp.color
        w2.update_makespan()

    # worker1 check if worker2_box is better
    def negotiate(self, worker_1, worker_2):
        # no targeted box, no neg
        if worker_1.target_box is None and worker_2.target_box is None:
            return
        if worker_2.target_box is None:
            return

        new_makespan_w1 = self.recalculate_makespan(worker_1, worker_2)
        # new_makespan_w2 = self.recalculate_makespan(worker_2, worker_1)

        if new_makespan_w1 < worker_1.makespan:
            if self.model.debug['schedule']:
                print(self.msg, "worker", worker_1.unique_id, "swap with worker", worker_2.unique_id, 'old_makespan:',
                      worker_1.makespan, 'new_makespan:', new_makespan_w1)
            self.switch_box(worker_1, worker_2)
        # elif new_makespan_w2 < worker_2.makespan:
        #     if self.model.debug.schedule:
        #         print(self.msg, "worker", worker_2.unique_id, "swap with worker", worker_1.unique_id)
        #     self.switch_box(worker_2, worker_1)

    def assign(self, worker, box):
        worker.target_box = box
        worker.color = box.color
        box.targeted_by = worker

    def step(self):
        # initiate with greedy strategy
        if self.init:
            self.greedy_init()
            self.init = False
            return

        # renegotiate for each worker
        workers = list(self.get_agents_by_class(Worker))
        for w_i in range(len(workers) - 1):
            for w_j in range(w_i + 1, len(workers)):
                self.negotiate(workers[w_i], workers[w_j])

        # get unused
        unused_workers = [w for w in list(self.get_agents_by_class(Worker)) if w.target_box is None]
        left_boxes = [b for b in list(self.get_agents_by_class(Box)) if b.targeted_by is None]

        # check if a box was left and a worker is ready
        if len(left_boxes) > 0 and len(unused_workers) > 0:
            for w, b in zip(unused_workers, left_boxes):
                self.assign(w, b)

        super().step()
