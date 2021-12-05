from mesa.visualization.ModularVisualization import ModularServer, VisualizationElement
from mesa.visualization.modules import CanvasGrid, ChartModule
from mesa.visualization.UserParam import UserSettableParameter

from agents import Worker, Box, Destination
from model import Collecte

import numpy as np


class HistogramModule(VisualizationElement):
    package_includes = ["Chart.min.js"]
    local_includes = ["HistogramModule.js"]

    def __init__(self, bins, canvas_height, canvas_width):
        self.canvas_height = canvas_height
        self.canvas_width = canvas_width
        self.bins = bins
        new_element = "new HistogramModule({}, {}, {})"
        new_element = new_element.format(bins,
                                         canvas_width,
                                         canvas_height)
        self.js_code = "elements.push(" + new_element + ");"

    def render(self, model):
        makespan_vals = [agent.makespan for agent in model.get_agents_by_class(Worker)]
        hist = np.histogram(makespan_vals, bins=self.bins)[0]
        return [int(x) for x in hist]


def agent_portrayal(agent):
    if agent is None:
        return

    portrayal = {"Filled": "true"}

    if type(agent) is Destination:
        portrayal["Layer"] = 0
        portrayal["Shape"] = "rect"
        portrayal["w"] = 1
        portrayal["h"] = 1
        portrayal["Color"] = "green"

    elif type(agent) is Box:
        portrayal["Layer"] = 1
        portrayal["Shape"] = "rect"
        portrayal["w"] = .7
        portrayal["h"] = .7
        portrayal["text"] = agent.unique_id
        portrayal["text_color"] = "white"
        portrayal["Color"] = agent.color

    elif type(agent) is Worker:
        portrayal["Layer"] = 2
        portrayal["Shape"] = "circle"
        portrayal["r"] = 0.5
        portrayal["Color"] = agent.color
        portrayal["text"] = agent.unique_id
        portrayal["text_color"] = "black"
        portrayal["Filled"] = False

        if agent.target_box is not None:
            portrayal["text"] = str(agent.unique_id) + '_' + str(agent.target_box.unique_id)
            portrayal["text_color"] = "white"
            portrayal["Filled"] = True

    return portrayal


model_params = {
    "nb_workers": UserSettableParameter(
        "number",
        "Number of Workers",
        value=5
    ),
    "nb_boxes": UserSettableParameter(
        "number",
        "Number of Boxes",
        value=5
    ),
    "strategy": UserSettableParameter(
        "choice",
        "Strategy",
        value='Random',
        choices=['Random', 'Earliest Completion Time', 'Gift', 'Swap', 'Gift&Swap']
    ),
    "width": 10,
    "height": 10,
}

canvas_element = CanvasGrid(agent_portrayal, 10, 10, 500, 500)
chart = ChartModule([{"Label": "Makespan",
                      "Color": "Black"}],
                    data_collector_name='datacollector')
histogram = HistogramModule(list(range(10)), 200, 500)

server = ModularServer(
    Collecte, [canvas_element, chart, histogram], "Collecte Model", model_params
)
server.port = 8521
server.launch()
