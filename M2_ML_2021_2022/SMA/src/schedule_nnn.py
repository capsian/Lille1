from collections import defaultdict

from mesa.time import BaseScheduler

from agents import Worker, Box


class NaiveNearestNeighbors(BaseScheduler):

    def __init__(self, model):
        super().__init__(model)
        self.init = True
        self.agents_dict = defaultdict(dict)
        self.global_makespan = 0
        self.unused_workers = []
        self.msg = "schedule:nnn>"

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

    def update_unused_workers(self):
        self.unused_workers = []
        for w in self.get_agents_by_class(Worker):
            if w.target_box is None:
                self.unused_workers += [w]

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

    def step(self):
        # initiate with greedy strategy
        if self.init:
            self.greedy_init()
            self.init = False
            return

        # get workers who haven't a targeted_box
        self.update_unused_workers()

        # for each worker assign the nearest available box
        for w_i in range(len(self.unused_workers)):
            w_targeted_box = self.unused_workers[w_i].get_nearest_box()

            if w_targeted_box is not None:
                # assign box to worker
                w_targeted_box.targeted_by = self.unused_workers[w_i]
                # assign worker to box
                self.unused_workers[w_i].target_box = w_targeted_box
                # update worker color
                self.unused_workers[w_i].color = w_targeted_box.color
                if self.model.debug['schedule']:
                    print(self.msg, "unused worker", self.unused_workers[w_i], "target_box:",
                          self.unused_workers[w_i].target_box)

        super().step()
