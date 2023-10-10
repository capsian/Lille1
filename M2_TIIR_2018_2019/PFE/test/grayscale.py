import sys, os, logging, argparse

# TODO: improve import
sys.path.append(os.getcwd() + '/src')

from utils import *
from filters import *


def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-t",   "--times",      nargs=1,   help="apply n times");
    parser.add_argument("-wt",   "--width",      nargs=1,   help="width");
    parser.add_argument("-ht",   "--height",      nargs=1,  help="height");
    parser.add_argument("-v",   "--verbose",    nargs=1,   help="verbose mode : info | debug | warn | error ");

    args = parser.parse_args()

    if (args.width == None) or (args.height == None):
        print("Error input !")
        exit(1);

    if (args.verbose != None):
        loglevel = args.verbose[0]
        numeric_level = getattr(logging, loglevel.upper(), None)
        if not isinstance(numeric_level, int):
            raise ValueError('Invalid log level: %s' % loglevel)
        logging.basicConfig(level=numeric_level)

    logging.debug("args = %s" % args)


    return args

def main():

    args = arg_parser()

    logging.basicConfig(level=logging.DEBUG)

    i_max, j_max = int(args.width[0]), int(args.height[0]);
    mat = np.arange(int(args.width[0]) * int(args.height[0])).reshape(int(args.height[0]), int(args.width[0]))
    res = np.arange(int(args.width[0]) * int(args.height[0])).reshape(int(args.height[0]), int(args.width[0]))

    print("Generating matrix : ")
    for i in range(i_max):
        for j in range (j_max):
            pxl = input("(%d,%d) value = " % (i,j))
            mat[i][j] = pxl
        print()

    print("Matrix = ")
    for i in range(i_max):
        for j in range(j_max):
            print("(%d)" % mat[i][j], end='');
        print();

    print("TOR : ")
    if (args.times != None):
        for k in range(int(args.times[0])):
            for i in range(i_max):
                for j in range(j_max):
                    if k == 0:
                        res[i][j] = get_tor(get_neighbours(mat, i, j, i_max - 1, j_max - 1))[0]
                    else:
                        res[i][j] = get_tor(get_neighbours(res, i, j, i_max - 1, j_max - 1))[0]
            print("Result %d = " % k)
            for i in range(i_max):
                for j in range(j_max):
                    print("(%d)" % res[i][j], end='');
                print();
    else:
        for i in range(i_max):
            for j in range(j_max):
                res[i][j] = get_tor(get_neighbours(mat, i, j, i_max - 1, j_max - 1))[0]
        print("Result = ")
        for i in range(i_max):
            for j in range(j_max):
                print("(%d)" % res[i][j], end='');
            print();

    return 0

if __name__ == "__main__":
    main()