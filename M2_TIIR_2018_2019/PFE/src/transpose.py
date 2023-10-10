import argparse
from PIL import Image
from tqdm import tqdm

from const import *
from filters import *
from utils import *


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
    pix_in = np.array(Image.open(args.input[0]).convert('L'))

    # init result img (uint8=[0,255])
    pix_res = pix_in.transpose()

    # Save
    new_img = Image.fromarray(pix_res)
    new_img.save(args.out[0], "JPEG")

    return 0

if __name__ == "__main__":
    main()
