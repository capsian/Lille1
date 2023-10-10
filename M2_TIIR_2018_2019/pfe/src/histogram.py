import cv2
import os, argparse

import matplotlib
matplotlib.use('Agg')
from matplotlib import pyplot as plt

def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-o",   "--output",     nargs=1,   help="output histogram");
    parser.add_argument("-i",   "--input",       nargs='+',help="input image");
    args = parser.parse_args()

    if (args.input == None) or (args.output == None):
        print("Error input !")
        exit(1);

    return args

def main():

    args = arg_parser();

    img = cv2.imread(args.input[0], 0)

    # alternative way to find histogram of an image
    plt.hist(img.ravel(), 256, [0, 256])
    #plt.show()

    plt.savefig(args.output[0])

    return 0

if __name__ == "__main__":
    main()