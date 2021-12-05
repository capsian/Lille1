from mesa.visualization.ModularVisualization import ModularServer
from mesa.visualization.modules import CanvasGrid
from mesa.visualization.UserParam import UserSettableParameter

from .agents import Worker,Box,Destination
from .model import Collecte

def agent_portrayal(agent):
    if agent is None:
        return

    portrayal = {"Filled":"true"}

    if type(agent) is Box:

        if (agent.targeted):
            portrayal["text"] = agent.unique_id
            portrayal["text_color"] = "white"
            portrayal["Shape"] = "circle"
            portrayal["r"] = 0.5
            portrayal["Color"] = "green"
            portrayal["Layer"] = 2
        else:
            portrayal["text"] = agent.unique_id
            portrayal["text_color"] = "white"
            portrayal["Shape"] = "circle"
            portrayal["r"] = 0.3
            portrayal["Color"] = "grey"
            portrayal["Layer"] = 2
    elif type(agent) is Worker:
        portrayal["Shape"] = "rect"
        portrayal["w"] = 0.7
        portrayal["h"] = 0.7
        portrayal["Color"] = "red"
        portrayal["Layer"] = 1
        if (agent.target is not None):
            portrayal["text"] = agent.target.unique_id
            portrayal["text_color"] = "white"

    elif type(agent) is Destination:
        portrayal["Shape"] = "rect"
        portrayal["w"] = 0.9
        portrayal["h"] = 0.9
        portrayal["Color"] = "blue"
        portrayal["Layer"] = 0

    return portrayal

model_params = {
    "nb_workers": UserSettableParameter(
        "number",
        "Number of Workers",
        value=5
    ),
    "nb_boites": UserSettableParameter(
        "number",
        "Number of Boxes",
        value=5
    ),
    "strategy": UserSettableParameter(
        "choice",
        "Strategy",
        value='Default Strategy',
        choices=['Default Strategy', 'Alternate Strategy']
    ),
    "width": 10,
    "height": 10,
}


canvas_element = CanvasGrid(agent_portrayal, 10,10, 500, 500)
server = ModularServer(
    Collecte, [canvas_element], "Collecte Model", model_params
)
server.port=8521
# server.launch()
