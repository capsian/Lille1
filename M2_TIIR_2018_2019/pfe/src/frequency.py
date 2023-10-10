import os, argparse
from PIL import Image
import numpy as np

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

from filters import *
from utils import *
from const import *

def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i",   "--input",      nargs=1,   help="input image");
    parser.add_argument("-o",   "--out",        nargs=1,   help="output file");

    args = parser.parse_args()

    if (args.input == None) or (args.out == None):
        print("Error input !")
        exit(1);

    return args

def main():

    args = arg_parser()

    # Read image & get pixels
    pix_in = np.array(Image.open(args.input[0]))

    # enable out of docker
    plt.plot(get_frequency(pix_in))

    plt.savefig(args.out[0])

    return 0

if __name__ == "__main__":
    main()
