from mesa import Agent
import numpy as np
import math

def get_distance(pos_1, pos_2):
    """Get the distance between two point
    Args:
        pos_1, pos_2: Coordinate tuples for both points.
    """
    x1, y1 = pos_1
    x2, y2 = pos_2
    dx = x1 - x2
    dy = y1 - y2
    return math.sqrt(dx ** 2 + dy ** 2)


class Worker(Agent):

    def __init__(self,pos,model,capacity=10):
        super().__init__(pos, model)
        self.capacity = capacity
        self.in_work = False
        self.target_pos = None
        self.target = None
        self.carry = None

    def move(self):

        # get neighbors
        x, y = self.pos
        neighbors = []
        neighbors.append((x+1, y))
        neighbors.append((x-1, y))
        neighbors.append((x, y+1))
        neighbors.append((x, y-1))

        possible_steps = [
            i for i in neighbors if not self.model.grid.out_of_bounds(i)
        ]

        # calculate distance for each possible_steps
        dist = []
        for ps in possible_steps:
            dist += [get_distance(ps, self.target_pos)]
        best_move = np.argmin(dist)
        best_move = possible_steps[best_move]




        print(self.unique_id, 'i will go to ', self.target_pos)
        # new_position = self.random.choice(possible_steps)
        self.model.grid.move_agent(self, best_move)
        if (self.carry is not None):
            self.model.grid.move_agent(self.carry, best_move)




    def step(self):
        print ("target",self.target)
        if (self.pos==self.target_pos):
            if (type(self.target)==Box):
                self.carry = self.model.schedule.agents_by_breed[Box][self.target.unique_id]
                self.target = self.model.schedule.agents_by_breed[Destination][self.model.current_id]
                self.target_pos = self.target.pos
            elif ((type(self.target)==Destination)&(self.carry is not None)):
                self.model.grid._remove_agent(self.carry.pos, self.carry)
                self.model.schedule.remove(self.carry)
                self.carry = None
                self.target = None

        else:
            self.move()

class Box(Agent):
    def __init__(self,pos,model,weight=5):
        super().__init__(pos, model)
        self.weight = weight
        self.targeted = False
        self.delivered = False


class Destination(Agent):
    def __init__(self,pos,model):
        super().__init__(pos, model)
