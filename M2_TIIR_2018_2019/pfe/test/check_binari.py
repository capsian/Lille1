import sys, os, logging, argparse
from PIL import Image

# TODO: improve import
sys.path.append(os.getcwd() + '/src')

from utils import *
from const import *
from filters import *


def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i",   "--input",      nargs=1,   help="input");
    parser.add_argument("-v",   "--verbose",    nargs=1,   help="verbose mode : info | debug | warn | error ");

    args = parser.parse_args()

    if (args.input == None):
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

    pix_in = np.array(Image.open(args.input[0]))

    for i in range(I_MAX):
        for j in range(J_MAX):
            if (pix_in[i][j][0] != 0) or (pix_in[i][j][0] != 255):
                print("ERROR %s" % pix_in[i][j])

    return 0

if __name__ == "__main__":
    main()