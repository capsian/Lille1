from collections import defaultdict

from mesa.time import RandomActivation

from agents import Worker, Box


class Heuristique1(RandomActivation):

    def __init__(self, model):
        super().__init__(model)
        self.init = True
        self.agents_dict = defaultdict(dict)
        self.global_makespan = 0
        self.unused_workers = []
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

    def update_unused_workers(self):
        self.unused_workers = []
        for w in self.get_agents_by_class(Worker):
            if w.target_box is None:
                self.unused_workers += [w]

    def step(self):
        # get workers who haven't a targeted_box
        self.update_unused_workers()
        # for each available box starting from the highest etc_priority, assign the closest worker
        available_boxes = []
        for b in self.get_agents_by_class(Box):
            if b.targeted_by is None:
                available_boxes += [b]
        # The boxes with the highest priority are the boxes who appeared first
        available_boxes_desc = sorted(available_boxes, key=lambda x: x.etc_priority)
        print(a.unique_id for a in available_boxes_desc)
        for b in available_boxes_desc:
            # If there are some unused workers, pick the closest to the box
            if len(self.unused_workers) != 0:
                closest_worker = b.get_nearest_worker()
                closest_worker.target_box = b
                b.targeted_by = closest_worker
                closest_worker.color = b.color
                if self.model.debug['schedule']:
                    print(self.msg, "worker", closest_worker.unique_id, "targeted box:",
                          b.unique_id)
                    # On retire closest_worker de la liste des unused workers
                self.update_unused_workers()

        super().step()
