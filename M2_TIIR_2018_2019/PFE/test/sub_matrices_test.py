import numpy as np
import sys, os, logging

# TODO: improve import
sys.path.append(os.getcwd() + '/src')

from utils import *

def main():

    logging.basicConfig(level=logging.DEBUG)

    i_max, j_max = 16, 16;
    edge = 4
    mat = np.arange(256).reshape(16, 16)

    print("Generating matrix : ")
    for i in range(i_max):
        for j in range (j_max):
            print("(%d)" % mat[i][j], end='');
        print();
    print();

    blocks_pos = get_blocks_pos(edge, i_max, j_max, 2);

    print("We fill the submatrices")
    for i in range(0, len(blocks_pos), 2):
        fill_sub_matrix(mat, blocks_pos[i], blocks_pos[i+1], i);

    print("Result = ")
    for i in range(i_max):
        for j in range (j_max):
            print("(%d)" % mat[i][j], end='');
        print();

    return 0

if __name__ == "__main__":
    main()