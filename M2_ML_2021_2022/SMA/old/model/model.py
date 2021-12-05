from mesa import Model
from mesa.space import MultiGrid
from mesa.datacollection import DataCollector

from .agents import Worker,Box,Destination
from .schedule import RandomActivationByBreed

class Collecte(Model):
    def __init__(self,nb_workers,nb_boites,strategy,width=10,height=10):
        self.nb_workers = nb_workers
        self.nb_boites = nb_boites
        self.strategy = strategy
        self.grid = MultiGrid(height,width,True)
        self.current_id=-1
        self.running=True
        self.schedule = RandomActivationByBreed(self)

        # add workers
        for i in range(self.nb_workers):
            a = Worker(self.next_id(), self)
            self.schedule.add(a)
            x = self.random.randrange(self.grid.width)
            y = self.random.randrange(self.grid.height)
            self.grid.place_agent(a, (x, y))

        # add boxes
        for j in range(self.nb_boites):
            a = Box(self.next_id(), self)
            self.schedule.add(a)
            x = self.random.randrange(self.grid.width)
            y = self.random.randrange(self.grid.height)
            self.grid.place_agent(a, (x, y))

        # add destination
        a = Destination(self.next_id(), self)
        self.schedule.add(a)
        x = self.random.randrange(self.grid.width)
        y = self.random.randrange(self.grid.height)
        self.grid.place_agent(a, (x, y))

        # assign each box to worker and each worker to the targeted box
        w_i = 0
        for b_id in self.schedule.agents_by_breed[Box]:
            b = self.schedule.agents_by_breed[Box][b_id]
            b.targeted = self.schedule.agents_by_breed[Worker][w_i]
            self.schedule.agents_by_breed[Worker][w_i].target_pos = b.pos
            self.schedule.agents_by_breed[Worker][w_i].target = b
            w_i += 1

    def step(self):
        self.schedule.step()
        print('boxes', self.schedule.agents_by_breed[Box])
