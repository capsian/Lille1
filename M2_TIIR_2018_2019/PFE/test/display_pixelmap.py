from PIL import Image
import sys, os, logging, argparse

# TODO: improve import
sys.path.append(os.getcwd() + '/src')

from utils import *
from src.filters import *
from const import *


def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i",   "--input",      nargs=1,   help="input image");

    args = parser.parse_args()

    if (args.input == None):
        print("Error input !")
        exit(1);

    logging.debug("args = %s" % args)

    return args

def main():

    logging.basicConfig(level=logging.DEBUG)

    args = arg_parser()

    # Read image & get pixels
    pix_in = np.array(Image.open(args.input[0]))

    for i in range(I_MAX):
        for j in range(J_MAX):
            if (pix_in[i][j][0] != pix_in[i][j][1]) or (pix_in[i][j][0] != pix_in[i][j][2]) or (pix_in[i][j][1] != pix_in[i][j][2]):
                print("ERROR %s" % pix_in[i][j])

    print("all ok")

    return 0

if __name__ == "__main__":
    main()