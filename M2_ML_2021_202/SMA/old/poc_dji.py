import numpy as np

# The list needs to be transformed into an array in order to use the np.where method
# arr = np.random.randint(5, size=(6, 6))
arr = np.array([[0, 0, 0, 1, 1, 3],
                [0, 0, 3, 1, 1, 0],
                [0, 0, 1, 3, 1, 1],
                [3, 0, 3, 1, 1, 1], ])

print(arr)

# Origin cell to make the search
x0, y0 = (0, 0)
targetValue = 3

# This is the keypoint of the problem: find the positions of the cells containing the searched value
positions = np.where(arr == targetValue)
x, y = positions
print("positions:", positions)

dx = abs(x0 - x)  # Horizontal distance
dy = abs(y0 - y)  # Vertical distance

print("dx:", dx)
print("dy:", dy)


# There are different criteria to compute distances
euclidean_distance = np.sqrt(dx ** 2 + dy ** 2)
manhattan_distance = abs(dx + dy)
my_distance = euclidean_distance  # Criterion choice
min_dist = min(my_distance)
print('min_dist:', min_dist)
print("manhattan_distance", manhattan_distance, "min:", min(manhattan_distance))

min_pos = np.argmin(my_distance)  # This method will only return the first occurrence (!)
min_pos2 = np.argmin(manhattan_distance)
min_coords = x[min_pos], y[min_pos]
min_coords2 = x[min_pos2], y[min_pos2]
print('min_coords:', min_coords)
print('min_coords2:', min_coords2)