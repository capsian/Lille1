from mesa import Agent

import numpy as np
import collections


def manhattan_dist(pos_1, pos_2):
    """Get the distance between two point
    Args:
        pos_1, pos_2: Coordinate tuples for both points.
    """
    x1, y1 = pos_1
    x2, y2 = pos_2
    dx = abs(x1 - x2)
    dy = abs(y1 - y2)
    return dx + dy


class Worker(Agent):

    def __init__(self, pos, model, dest_pos, capacity=1):
        super().__init__(pos, model)
        self.capacity = capacity
        self.carry = False
        self.target_box = None
        self.dest_pos = dest_pos
        self.color = 'grey'
        self.makespan = 0
        self.msg = "agent:worker:" + str(self.unique_id) + ">"
        self.old_pos = pos

    def get_neighbors(self, pos=None):
        # get neighbors
        x, y = self.pos
        if pos is not None:
            x, y = pos

        neighbors = [
            (x + 1, y),
            (x - 1, y),
            (x, y + 1),
            (x, y - 1),
        ]
        # remove out of bonds
        possible_neighbors = [
            i for i in neighbors if not self.model.grid.out_of_bounds(i)
        ]
        return possible_neighbors

    def get_possible_steps(self, neighbors):
        possible_steps = []
        for n in neighbors:
            cell_contents = self.model.grid.get_cell_list_contents(n)
            # empty cell
            if len(cell_contents) == 0:
                possible_steps += [n]
            else:
                for cell_content in cell_contents:
                    # allow cross destination cell
                    if type(cell_content) is Destination:
                        possible_steps += [n]
                    # allow cross to targeted_box
                    elif cell_content == self.target_box:
                        possible_steps += [n]
        return possible_steps

    def move(self):
        # get possible neighbors step
        neighbors = self.get_neighbors()

        # remove not empty cell
        possible_steps = self.get_possible_steps(neighbors)
        if len(possible_steps) == 0:
            if self.model.debug['agents']:
                print(self.msg, 'cant move !')
            return

        if self.model.debug['agents']:
            print(self.msg, "possible_steps:", possible_steps)

        # calculate distance for each possible_steps
        # carry box, go to dest
        if self.carry:
            tmp_target = self.dest_pos
        # not carrying box, go to target_box
        else:
            tmp_target = self.target_box.pos

        dist = []
        for ps in possible_steps:
            dist += [manhattan_dist(ps, tmp_target)]

        # simulate a step ahead to prevent deadlock
        d_i = 0
        for ps in possible_steps:
            ns = self.get_neighbors(pos=ps)
            possible_neighbors = self.get_possible_steps(ns)
            tmp = []
            for pn in possible_neighbors:
                tmp += [manhattan_dist(pn, tmp_target)]
            if len(tmp) > 0:
                dist[d_i] += np.argmin(tmp)

        if self.model.debug['agents']:
            print(self.msg, "carry:", self.carry, "old_makespan:", self.makespan, "dist:", dist)

        # check if we shouldn't move !
        # tmp = [item for item, count in collections.Counter(dist).items() if count > 1]
        # if len(dist) == 0 or len(tmp) > 1:
        if len(dist) == 0:
            if self.model.debug['agents']:
                print(self.msg, "should not move !")
            return

        best_move = np.argmin(dist)
        best_move = possible_steps[best_move]
        if self.old_pos == best_move:
            if self.model.debug['agents']:
                print(self.msg, "same old pos no move !")
                return

        # move agent & his box if he carries it
        self.model.grid.move_agent(self, best_move)
        if self.carry:
            self.model.grid.move_agent(self.target_box, best_move)

    def update_makespan(self):
        if self.target_box is not None:
            self.makespan = 0
            if self.carry:
                self.makespan = manhattan_dist(self.pos, self.dest_pos)
            else:
                self.makespan = manhattan_dist(self.pos, self.target_box.pos)
                self.makespan += manhattan_dist(self.pos, self.dest_pos)

    def step(self):
        if self.model.debug['agents']:
            print(self.msg, "step, makespan:", self.makespan)

        # update makespan
        self.update_makespan()

        # worker have a targeted box
        if self.target_box is not None:
            # worker is on the same cell of target_box
            if self.pos == self.target_box.pos:
                if not self.carry:
                    # take the box
                    self.carry = True
            # worker is on destination cell
            if self.pos == self.dest_pos:
                if self.carry:
                    # drop & remove target_box
                    self.carry = False
                    self.target_box = None
                else:
                    # just pass over the dest
                    self.move()
            else:
                self.move()

        self.old_pos = self.pos

    def get_nearest_box(self):
        available_boxes = []
        for b in self.model.schedule.get_agents_by_class(Box):
            if b.targeted_by is None and b.weight <= self.capacity:
                available_boxes += [b]

        if len(available_boxes) == 0:
            return None

        # calc distances
        dist = []
        for b in available_boxes:
            dist += [manhattan_dist(self.pos, b.pos)]

        return available_boxes[np.argmin(dist)]


class Box(Agent):
    def __init__(self, pos, model, color="grey", weight=5):
        super().__init__(pos, model)
        self.color = color
        self.weight = weight
        self.targeted_by = None
        # Plus la boite apparait tot, plus elle est prioritaire dans cette heuristique
        self.etc_priority = self.unique_id

    def step(self):
        if self.targeted_by is not None:
            if self.pos == self.targeted_by.dest_pos:
                if self.model.debug['agents']:
                    print("agent:box" + str(self.unique_id) + "> arrived !")
                # remove box
                self.model.schedule.remove(self)

    # Return the nearest worker from the box
    def get_nearest_worker(self):
        available_workers = []
        for w in self.model.schedule.get_agents_by_class(Worker):
            if w.target_box is None and self.weight <= w.capacity:
                available_workers += [w]

        if len(available_workers) == 0:
            return None

        # calc distances
        dist = []
        for w in available_workers:
            dist += [manhattan_dist(self.pos, w.pos)]

        return available_workers[np.argmin(dist)]


class Destination(Agent):
    def __init__(self, pos, model):
        super().__init__(pos, model)
