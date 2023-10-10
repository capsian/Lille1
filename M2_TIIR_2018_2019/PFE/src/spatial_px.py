import os, argparse
from PIL import Image
from tqdm import tqdm
import numpy as np

from filters import *
from utils import *
from const import *

def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i",   "--input",      nargs=1,   help="input image");
    parser.add_argument("-o",   "--out",        nargs=1,   help="output file");
    parser.add_argument("-c",   "--calculate",  nargs=1,   help="caculate : mean [1] | median [2] | standard variation [3]");
    parser.add_argument("-s",   "--skip",       nargs=1,   help="skip n pixels (for x&y)");

    args = parser.parse_args()

    if (args.input == None) or (args.calculate == None) or (args.out == None):
        print("Error input !")
        exit(1);

    return args

def main():

    args = arg_parser()

    # Read image & get pixels
    pix_in = np.array(Image.open(args.input[0]))

    # init result img (uint8=[0,255])
    pix_res = np.zeros((I_MAX, J_MAX, 3), dtype=np.uint8)

    if (args.skip == None):
        # construct new img pixel per pixel
        for i in tqdm(range(0, I_MAX - 1)):
            for j in range(0, J_MAX - 1):
                neighbours = get_neighbours(pix_in, i, j, I_MAX - 1, J_MAX - 1)

                # calculate, return [r,g,b]
                stats = get_stats(neighbours, int(args.calculate[0]))

                # fill the new pxl
                pix_res[i][j] = (int(stats[0]), int(stats[1]), int(stats[2]))
    else:
        # construct new img pixel per pixel
        for i in tqdm(range(0, I_MAX - 1, int(args.skip[0]))):
            for j in range(0, J_MAX - 1, int(args.skip[0])):
                neighbours = get_neighbours(pix_in, i, j, I_MAX - 1, J_MAX - 1)

                # calculate, return [r,g,b]
                stats = get_stats(neighbours, int(args.calculate[0]))

                # fill the new pxl
                for m in range(int(args.skip[0])):
                    for n in range(int(args.skip[0])):
                        #print("pxil (%d,%d)" % (i+m,j+n))
                        pix_res[i+m][j+n] = (int(stats[0]), int(stats[1]), int(stats[2]))
                #print()


    # Save
    new_img = Image.fromarray(pix_res)
    new_img.save(args.out[0], "JPEG")

    return 0

if __name__ == "__main__":
    main()
