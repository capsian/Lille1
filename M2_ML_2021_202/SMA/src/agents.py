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

    def __init__(self, pos, model, dest_pos, capacity=1):
        super().__init__(pos, model)
        self.capacity = capacity
        self.carry = False
        self.target_box = None
        self.dest_pos = dest_pos
        self.color = 'grey'
        self.makespan = 0

    def move(self):

        # get neighbors
        x, y = self.pos
        neighbors = [
            (x + 1, y),
            (x - 1, y),
            (x, y + 1),
            (x, y - 1),
        ]
        # remove out of bonds
        possible_steps = [
            i for i in neighbors if not self.model.grid.out_of_bounds(i)
        ]

        # calculate distance for each possible_steps
        dist = []
        # carry box, go to dest
        if self.carry:
            tmp_target = self.dest_pos
        # not carrying box, go to target_box
        else:
            tmp_target = self.target_box.pos

        for ps in possible_steps:
            dist += [get_distance(ps, tmp_target)]

        best_move = np.argmin(dist)
        best_move = possible_steps[best_move]

        # move agent & his box if he carries it
        self.model.grid.move_agent(self, best_move)
        if self.carry:
            self.model.grid.move_agent(self.target_box, best_move)

    def step(self):
        # update makespan
        self.makespan += 1

        # worker have a targeted box
        if self.target_box is not None:
            # worker is on the same cell of target_box
            if self.pos == self.target_box.pos:
                if not self.carry:
                    self.carry = True
            # worker is on destination cell
            if self.pos == self.dest_pos:
                if self.carry:
                    self.carry = False
                    # remove box
                    self.model.schedule.remove(self.target_box)
                    # remove target_box
                    self.target_box = None
                else:
                    # just pass over the dest
                    self.move()
            else:
                self.move()


class Box(Agent):
    def __init__(self, pos, model, color="grey", weight=5):
        super().__init__(pos, model)
        self.color = color
        self.weight = weight
        self.targeted_by = None


class Destination(Agent):
    def __init__(self, pos, model):
        super().__init__(pos, model)
