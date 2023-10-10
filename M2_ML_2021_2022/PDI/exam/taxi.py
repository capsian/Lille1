import numpy as np


N = 3 # nb of states
M = 3 # nb of actions
P = np.array ([[[1/2, 1/4, 1/4],
                [1/16, 3/4, 3/16],
                [1/4, 1/8, 5/8]],
               [[1/2, 0, 1/2],
                [0,0,0],
                [1/16, 7/8, 1/16]],
               [[1/4, 1/4, 1/2],
                [1/8, 3/4, 1/8],
                [3/4, 1/16, 3/16]]])
                
R = np.array ([10, 4, 8, 8, 2, 4, 4, 6, 4, 14, 0, 18, 0, 0, 0, 8, 16, 8, 10, 2, 8, 6, 4, 2, 4, 0, 8])
R = R.reshape ([N, M, N])

pi = [
	[1/3, 1/3, 1/3],
	[1/2, 0, 1/2],
	[1/3, 1/3, 1/3]
]

print('P:', P)
print('R:', R)


tmp = P@R
print('tmp:', tmp)

tmp2 = pi@tmp
print('tmp2:', tmp2)