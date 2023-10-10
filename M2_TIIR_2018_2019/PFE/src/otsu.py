import argparse, os
from PIL import Image

import mahotas
import mahotas.demos
from pylab import imshow, gray, show

from const import *
from filters import *
from utils import *


def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i",   "--input",      nargs=1,   help="input image");

    args = parser.parse_args()

    if (args.input == None):
        print("Error input !")
        exit(1);

    return args

def main():

    args = arg_parser()

    # Read image & get pixels
    pix_in = np.array(Image.open(args.input[0]))

    T_otsu = mahotas.otsu(pix_in)
    print(T_otsu)
    imshow(pix_in > T_otsu)
    show()

    return 0

if __name__ == "__main__":
    main()
