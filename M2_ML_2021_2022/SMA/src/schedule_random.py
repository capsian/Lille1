from collections import defaultdict

import numpy as np
from mesa.time import RandomActivation

from agents import Box, Worker


class Random(RandomActivation):

    def __init__(self, model):
        super().__init__(model)
        self.agents_dict = defaultdict(dict)
        self.unused_workers = []
        self.msg = "schedule:random>"

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

    def get_random_box(self, worker):
        available_boxes = []
        for b in self.get_agents_by_class(Box):
            if b.targeted_by is None and b.weight <= worker.capacity:
                available_boxes += [b]

        if len(available_boxes) == 0:
            return None

        # get a random box
        next_id = np.random.randint(len(available_boxes))

        return available_boxes[next_id]

    def update_unused_workers(self):
        self.unused_workers = []
        for w in self.get_agents_by_class(Worker):
            if w.target_box is None:
                self.unused_workers += [w]

    def step(self):
        # get workers who haven't a targeted_box
        self.update_unused_workers()
        # for each worker assign the nearest available box
        for w_i in range(len(self.unused_workers)):
            w_targeted_box = self.get_random_box(self.unused_workers[w_i])
            if w_targeted_box is not None:
                # assign box to worker
                w_targeted_box.targeted_by = self.unused_workers[w_i]
                # assign worker to box
                self.unused_workers[w_i].target_box = w_targeted_box
                # update worker color
                self.unused_workers[w_i].color = w_targeted_box.color
                if self.model.debug['schedule']:
                    print(self.msg, "worker", self.unused_workers[w_i].unique_id, "targeted box:",
                          w_targeted_box.unique_id)

        super().step()
