from collections import defaultdict

from mesa.time import RandomActivation
from agents import Worker, Box, Destination, manhattan_dist

import itertools
import numpy as np


class ECT(RandomActivation):

    def __init__(self, model):
        super().__init__(model)
        self.start = True
        self.agents_dict = defaultdict(dict)
        self.global_makespan = 0
        self.msg = "schedule:etc>"

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

    def calculate_makespan(self, worker, box):
        ms = manhattan_dist(worker.pos, box.pos)
        ms += manhattan_dist(box.pos, worker.dest_pos)
        return ms

    def get_combinations(self, unused_workers=None, left_boxes=None):

        if unused_workers is None and left_boxes is None:
            workers = list(self.get_agents_by_class(Worker))
            boxes = list(self.get_agents_by_class(Box))
            workers = [w for w in workers if w.target_box is None]
            boxes = [b for b in boxes if b.targeted_by is None]
        else:
            workers = unused_workers
            boxes = left_boxes

        unique_combinations1 = []
        permut1 = itertools.permutations(workers, len(boxes))
        for comb in permut1:
            zipped = zip(comb, boxes)
            unique_combinations1.append(list(zipped))

        unique_combinations2 = []
        permut2 = itertools.permutations(boxes, len(workers))
        for comb in permut2:
            zipped = zip(comb, workers)
            unique_combinations2.append(list(zipped))

        if self.model.debug['schedule']:
            print("unique_combinations1:", len(unique_combinations1))
            print("unique_combinations2:", len(unique_combinations2))

        unique_combinations = None
        reverse = False
        if len(unique_combinations1) != len(unique_combinations2):
            if len(unique_combinations1) == 0:
                reverse = True
                unique_combinations = unique_combinations2
            if len(unique_combinations2) == 0:
                unique_combinations = unique_combinations1
        else:
            unique_combinations = unique_combinations1

        if unique_combinations is None:
            print(self.msg, "Error: couldn't get all permutation !!")
            exit()

        return unique_combinations, reverse

    def get_best_moves(self, unique_combinations, reverse):
        makespans = []
        for c in unique_combinations:
            res = 0
            for affectation in c:
                if reverse:
                    res += self.calculate_makespan(affectation[1], affectation[0])
                else:
                    res += self.calculate_makespan(affectation[0], affectation[1])

            makespans += [res]

        min_pos = np.argmin(makespans)
        if self.model.debug['schedule']:
            print(self.msg, "minimum makespan:", makespans[min_pos], "affectation:", unique_combinations[min_pos])

        return unique_combinations[min_pos]

    def associate(self, best_moves, reverse):
        if reverse:
            for b, w in best_moves:
                w.target_box = b
                w.color = b.color
                b.targeted_by = w
        else:
            for w, b in best_moves:
                w.target_box = b
                w.color = b.color
                b.targeted_by = w

    def init(self):
        self.start = False

        unique_combinations, reverse = self.get_combinations()
        best_moves = self.get_best_moves(unique_combinations, reverse)
        self.associate(best_moves, reverse)

    def step(self):
        # init
        if self.start:
            self.init()

        # get unused
        unused_workers = [w for w in list(self.get_agents_by_class(Worker)) if w.target_box is None]
        left_boxes = [b for b in list(self.get_agents_by_class(Box)) if b.targeted_by is None]

        # check if a box was left and a worker is ready
        if len(left_boxes) > 0 and len(unused_workers) > 0:
            unique_combinations, reverse = self.get_combinations(unused_workers=unused_workers, left_boxes=left_boxes)
            best_moves = self.get_best_moves(unique_combinations, reverse)
            self.associate(best_moves, reverse)

        super().step()
