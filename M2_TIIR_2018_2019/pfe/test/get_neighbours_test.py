import numpy as np
import sys, os, logging

# TODO: improve import
sys.path.append(os.getcwd() + '/src')

from utils import *

def main():

    logging.basicConfig(level=logging.DEBUG)

    i_max, j_max = 8, 8;
    mat = np.arange(64).reshape(8, 8)

    print("Generating matrix : ")
    for i in range(i_max):
        for j in range (j_max):
            print("(%d,%d|%d) " % (i,j,mat[i][j]), end='');
        print();
    print();

    i,j = 5,5;
    logging.debug("get_neighbours: i = %d, j = %d \n%s" % (i,j,get_neighbours(mat, i,j,i_max, j_max)));


    return 0

if __name__ == "__main__":
    main()