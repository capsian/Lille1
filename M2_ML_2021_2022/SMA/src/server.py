from mesa.visualization.ModularVisualization import ModularServer, VisualizationElement
from mesa.visualization.modules import CanvasGrid, ChartModule
from mesa.visualization.UserParam import UserSettableParameter

from agents import Worker, Box, Destination
from model import Collecte

import numpy as np
import json


class BarChartModuleCustom(VisualizationElement):
    package_includes = ["d3.min.js", "BarChartModule.js"]

    def __init__(
            self,
            fields,
            scope="model",
            sorting="none",
            sort_by="none",
            canvas_height=400,
            canvas_width=800,
            data_collector_name="datacollector",
    ):

        self.scope = scope
        self.fields = fields
        self.sorting = sorting
        self.canvas_height = canvas_height
        self.canvas_width = canvas_width
        self.data_collector_name = data_collector_name

        fields_json = json.dumps(self.fields)
        new_element = "new BarChartModule({}, {}, {}, '{}', '{}')"
        new_element = new_element.format(
            fields_json, canvas_width, canvas_height, sorting, sort_by
        )
        self.js_code = "elements.push(" + new_element + ")"

    def render(self, model):
        current_values = []
        data_collector = getattr(model, self.data_collector_name)

        if self.scope == "agent":
            df = data_collector.get_agent_vars_dataframe().astype("float")
            latest_step = df.index.levels[0][-1]
            labelStrings = [f["Label"] for f in self.fields]
            dict = df.loc[latest_step].T.loc[labelStrings].to_dict()
            current_values = list(dict.values())

        elif self.scope == "model":
            outDict = {}
            for s in self.fields:
                name = s["Label"]
                try:
                    val = data_collector.model_vars[name][-1]
                except (IndexError, KeyError):
                    val = 0
                outDict[name] = val
            current_values.append(outDict)
        else:
            raise ValueError("scope must be 'agent' or 'model'")
        actual_current_values = []
        for k in current_values:
            if not np.isnan(k["mk"]):
                actual_current_values.append(k)
        return actual_current_values


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
        portrayal["text"] = "{" + str(agent.weight) + "}_" + str(agent.unique_id)
        portrayal["text_color"] = "white"
        portrayal["Color"] = agent.color

    elif type(agent) is Worker:
        portrayal["Layer"] = 2
        portrayal["Shape"] = "circle"
        portrayal["r"] = 0.7
        portrayal["Color"] = agent.color
        portrayal["text"] = '{' + str(agent.capacity) + "}_" + str(agent.unique_id)
        portrayal["text_color"] = "black"
        portrayal["Filled"] = True

        if agent.target_box is not None:
            portrayal["text"] = '{' + str(agent.capacity) + "}_" + str(agent.unique_id)
            portrayal["text_color"] = "white"

    return portrayal


model_params = {
    # Workers
    "nb_workers": UserSettableParameter(
        "number",
        "Number of Workers",
        value=5
    ),
    "min_worker_capacity": UserSettableParameter(
        "number",
        "Minimum Worker Capacity",
        value=1
    ),
    "max_worker_capacity": UserSettableParameter(
        "number",
        "Maximum Worker Capacity",
        value=2
    ),

    # Boxes
    "nb_boxes": UserSettableParameter(
        "number",
        "Number of Boxes",
        value=5
    ),
    "min_box_weight": UserSettableParameter(
        "number",
        "Minimum Box Weight",
        value=1
    ),
    "max_box_weight": UserSettableParameter(
        "number",
        "Maximum Box Weight",
        value=2
    ),

    # Strategy
    "strategy": UserSettableParameter(
        "choice",
        "Strategy",
        value='Random',
        choices=['Random', 'Naive Nearest Neighbors', 'Negotiation 1', 'Earliest Completion Time', 'Heuristique 1']
    ),
    "fixed": UserSettableParameter(
        "checkbox",
        "Fixed",
        value=True
    ),
    "width": 10,
    "height": 10
}
canvas_element = CanvasGrid(agent_portrayal, 10, 10, 500, 500)
chart = ChartModule([{"Label": "Global Makespan",
                      "Color": "Black"}],
                    data_collector_name='datacollector')
bar = BarChartModuleCustom(fields=[{"Label": "mk", "Color": "#3E8AAE"}],
                           scope="agent",
                           data_collector_name='datacollector')
server = ModularServer(
    Collecte, [canvas_element, chart, bar], "Collecte Model", model_params
)
server.port = 8521
server.launch()
