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

            if (i+j) % 2 == 0:
                mat[i][j] = 0
            else:
                mat[i][j] = 1

            print("(%d)" % mat[i][j], end='');
        print();
    print();

    print("Result = ")
    for i in range(i_max):
        for j in range (j_max):
            print("(%d)" % mat[i][j], end='');
        print();

    return 0

if __name__ == "__main__":
    main()