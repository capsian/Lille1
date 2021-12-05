from mesa import Model
from mesa.space import MultiGrid
from mesa.datacollection import DataCollector

from agents import Worker, Box, Destination
from ETC_schedule import ETC
from Random_schedule import Random

import random
import numpy as np


class Collecte(Model):
    def __init__(self, nb_workers, nb_boxes, strategy, width=10, height=10):
        self.grid = MultiGrid(height, width, True)
        self.running = True

        self.nb_workers = nb_workers
        self.nb_boxes = nb_boxes
        self.strategy = strategy
        self.current_id = -1

        # Choose strategy (each strategy is in a scheduler)
        if strategy == "Earliest Completion Time":
            self.schedule = ETC(self)
        elif strategy == "Random":
            self.schedule = Random(self)
        elif strategy == "Gift":
            # todo, random for now
            self.schedule = Random(self)
        elif strategy == "Swap":
            # todo, random for now
            self.schedule = Random(self)
        elif strategy == "Gift&Swap":
            # todo, random for now
            self.schedule = Random(self)
        print('strategy:', strategy)

        # add destination
        dest = Destination(self.next_id(), self)
        self.schedule.add(dest)
        dest_x = self.random.randrange(self.grid.width)
        dest_y = self.random.randrange(self.grid.height)
        self.grid.place_agent(dest, (dest_x, dest_y))

        max_weight = 5

        # add workers
        for i in range(self.nb_workers):
            w = Worker(self.next_id(), self, dest_pos=(dest_x, dest_y), capacity=np.random.randint(0, max_weight))
            self.schedule.add(w)
            placed = False
            while not placed:
                x = self.random.randrange(self.grid.width)
                y = self.random.randrange(self.grid.height)
                if self.grid.is_cell_empty((x, y)):
                    placed = True
                    self.grid.place_agent(w, (x, y))

        # add boxes
        for j in range(self.nb_boxes):
            b = Box(self.next_id(), self, color="#" + ''.join([random.choice('0123456789ABCDEF') for i in range(6)]), weight=np.random.randint(0, max_weight))
            self.schedule.add(b)
            placed = False
            while not placed:
                x = self.random.randrange(self.grid.width)
                y = self.random.randrange(self.grid.height)
                if self.grid.is_cell_empty((x, y)):
                    placed = True
                    self.grid.place_agent(b, (x, y))

        # collect data
        self.datacollector = DataCollector(
            model_reporters={"Makespan": self.get_makespans})

    def get_makespans(self):
        m = []
        for w in self.get_agents_by_class(Worker):
            m += [[w.makespan]]

    def get_agents_by_class(self, agent_class):
        return self.schedule.agents_dict[agent_class].values()

    def step(self):
        self.datacollector.collect(self)
        self.schedule.step()
