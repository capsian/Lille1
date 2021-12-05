from collections import defaultdict

from mesa.time import RandomActivation
from agents import Worker, Box, get_distance

import numpy as np


class Random(RandomActivation):

    def __init__(self, model):
        super().__init__(model)
        self.agents_dict = defaultdict(dict)

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
            if b.targeted_by is None:
                available_boxes += [b]

        if len(available_boxes) == 0:
            return None

        # get a random box
        next_id = np.random.randint(len(available_boxes))

        return available_boxes[next_id]

    def step(self):
        # get workers who haven't a targeted_box
        available_workers = []
        for w in self.get_agents_by_class(Worker):
            if w.target_box is None:
                available_workers += [w]

        # for each worker assign the nearest available box
        for w_i in range(len(available_workers)):
            w_targeted_box = self.get_random_box(available_workers[w_i])
            if w_targeted_box is not None:
                # assign box to worker
                w_targeted_box.targeted_by = available_workers[w_i]
                # assign worker to box
                available_workers[w_i].target_box = w_targeted_box
                # update worker color
                available_workers[w_i].color = w_targeted_box.color
                print("worker", w_i, "targeted box:", w_targeted_box.unique_id)

        super().step()
