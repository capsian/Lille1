import pandas as pd
from mesa import Model
from mesa.space import MultiGrid
from mesa.datacollection import DataCollector

from agents import Worker, Box, Destination, manhattan_dist
from schedule_nnn import NaiveNearestNeighbors
from schedule_random import Random
from schedule_h1 import Heuristique1
from schedule_ect import ECT

from schedule_nego1 import Negotiation1

import random
import numpy as np


class Collecte(Model):
    def __init__(self, nb_workers, min_worker_capacity, max_worker_capacity, nb_boxes, min_box_weight, max_box_weight,
                 strategy, fixed, width=10, height=10):
        self.grid = MultiGrid(height, width, True)
        self.running = True
        self.current_id = -1

        self.nb_workers = nb_workers
        self.nb_boxes = nb_boxes
        self.strategy = strategy
        self.fixed = fixed

        self.global_makespan = 0
        self.unused_workers = []

        self.debug = {
            'model': True,
            'schedule': True,
            'agents': False
        }
        self.msg = "model>"

        # Choose strategy (each strategy is in a scheduler)
        if strategy == "Random":
            self.schedule = Random(self)
        elif strategy == "Naive Nearest Neighbors":
            self.schedule = NaiveNearestNeighbors(self)
        elif strategy == "Earliest Completion Time":
            self.schedule = ECT(self)
        elif strategy == "Negotiation 1":
            self.schedule = Negotiation1(self)
        elif strategy == "Heuristique 1":
            self.schedule = Heuristique1(self)

        print('model: strategy:', strategy)


        # add destination
        dest = Destination(self.next_id(), self)
        self.schedule.add(dest)
        if self.fixed:
            dest_x = 5
            dest_y = 4
        else:
            dest_x = self.random.randrange(self.grid.width)
            dest_y = self.random.randrange(self.grid.height)
        self.grid.place_agent(dest, (dest_x, dest_y))
        self.dest_pos = (dest_x, dest_y)

        # add workers
        if self.fixed:
            w1 = Worker(self.next_id(), self, dest_pos=(5, 4), capacity=1)
            w2 = Worker(self.next_id(), self, dest_pos=(5, 4), capacity=1)
            w3 = Worker(self.next_id(), self, dest_pos=(5, 4), capacity=1)
            w4 = Worker(self.next_id(), self, dest_pos=(5, 4), capacity=1)
            w5 = Worker(self.next_id(), self, dest_pos=(5, 4), capacity=1)
            self.schedule.add(w1)
            self.schedule.add(w2)
            self.schedule.add(w3)
            self.schedule.add(w4)
            self.schedule.add(w5)
            self.grid.place_agent(w1, (1, 1))
            self.grid.place_agent(w2, (5, 6))
            self.grid.place_agent(w3, (7, 8))
            self.grid.place_agent(w4, (2, 1))
            self.grid.place_agent(w5, (6, 1))
        else:
            for i in range(self.nb_workers):
                w = Worker(self.next_id(), self, dest_pos=(dest_x, dest_y),
                        capacity=np.random.randint(min_worker_capacity, max_worker_capacity))
                self.schedule.add(w)
                placed = False
                while not placed:
                    x = self.random.randrange(self.grid.width)
                    y = self.random.randrange(self.grid.height)
                    if self.grid.is_cell_empty((x, y)):
                        placed = True
                        self.grid.place_agent(w, (x, y))

        # add boxes
        if self.fixed:
            b1 = Box(self.next_id(), self, color="#" + ''.join([random.choice('0123456789ABCDEF') for i in range(6)]), weight=1)
            b2 = Box(self.next_id(), self, color="#" + ''.join([random.choice('0123456789ABCDEF') for i in range(6)]), weight=1)
            b3 = Box(self.next_id(), self, color="#" + ''.join([random.choice('0123456789ABCDEF') for i in range(6)]), weight=1)
            b4 = Box(self.next_id(), self, color="#" + ''.join([random.choice('0123456789ABCDEF') for i in range(6)]), weight=1)
            b5 = Box(self.next_id(), self, color="#" + ''.join([random.choice('0123456789ABCDEF') for i in range(6)]), weight=1)
            self.schedule.add(b1)
            self.schedule.add(b2)
            self.schedule.add(b3)
            self.schedule.add(b4)
            self.schedule.add(b5)
            self.grid.place_agent(b1, (1, 3))
            self.grid.place_agent(b2, (5, 9))
            self.grid.place_agent(b3, (4, 8))
            self.grid.place_agent(b4, (3, 1))
            self.grid.place_agent(b5, (5, 1))
        else:
            for j in range(self.nb_boxes):
                b = Box(self.next_id(), self, color="#" + ''.join([random.choice('0123456789ABCDEF') for i in range(6)]),
                        weight=np.random.randint(min_box_weight, max_box_weight))
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
            model_reporters={"Global Makespan": self.get_makespans},
            agent_reporters={"mk": self.get_single_makespan})
        self.datacollector.collect(self)
        df = (self.datacollector.get_agent_vars_dataframe().astype("float"))

    def get_makespan_df(self):

        boxes = list(self.schedule.get_agents_by_class(Box))
        workers = list(self.schedule.get_agents_by_class(Worker))

        dist_mat = np.zeros((len(workers), len(boxes)))
        for w_i in range(len(workers)):
            for b_i in range(len(boxes)):
                dist_mat[w_i][b_i] = manhattan_dist(workers[w_i].pos, boxes[b_i].pos)
                dist_mat[w_i][b_i] += manhattan_dist(boxes[b_i].pos, workers[w_i].dest_pos)

        indexes = ['worker_' + str(w.unique_id) for w in workers]
        cols = ['box_' + str(b.unique_id) for b in boxes]

        df_makespan = pd.DataFrame(dist_mat, index=indexes, columns=cols)

        df_makespan.to_csv('report.csv')

        return df_makespan

    def step(self):
        self.datacollector.collect(self)
        self.schedule.step()

        # update global makespan
        self.global_makespan = sum([w.makespan for w in self.schedule.get_agents_by_class(Worker)])
        if self.debug['model']:
            print(self.msg, "golbal_makespan:", self.global_makespan)
            print(self.msg, "nb_availables_boxes:", len(self.schedule.get_agents_by_class(Box)))

        # stop simulation if no boxes left
        if len(self.schedule.get_agents_by_class(Box)) == 0:
            self.running = False

    def get_makespans(self):
        return self.global_makespan

    def get_single_makespan(self, agent):
        return getattr(agent, "makespan", None)
