import os, argparse
from PIL import Image
from tqdm import tqdm
import numpy as np

from filters import *
from utils import *
from const import *

def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i",   "--input",      nargs='+', help="input images list");
    parser.add_argument("-out", "--out",        nargs=1,   help="output file");
    parser.add_argument("-t",   "--threshold",  nargs=1,   help="threshold for the calculation");
    parser.add_argument("-c",   "--calculate",  nargs=1,   help="caculate : mean [1] | median [2] | standard variation [3]");

    args = parser.parse_args()

    if (args.input == None) or (args.out == None) or (args.calculate == None):
        print("Error input !")
        exit(1);

    return args

def main():

    args = arg_parser();

    # init result img (uint8=[0,255])
    pix_res = np.zeros((I_MAX, J_MAX, 3), dtype=np.uint8)

    # load imgs
    pxl_list = []
    for i in args.input:
        pxl_list.append(np.array(Image.open(i)))

    stat = [-1,-1,-1]

    # construct new img pixel per pixel through the time
    for i in tqdm(range(0, I_MAX - 1)):
        for j in range(0, J_MAX - 1):

            if (i+j) % 2 != 0:
                if stats[0] == -1:
                    print("SHOULD NEVER HAPPEN !!!")
                    return 1
                # fill the skiped pxl with the last
                pix_res[i][j] = (int(stats[0]), int(stats[1]), int(stats[2]))
                pass

            # get all neighbours of pxl[i,j] through the time
            nghbrs_list = []
            for elem in pxl_list:
                nghbrs_list += get_neighbours(elem, i, j, I_MAX - 1, J_MAX - 1)

            # calculate, return [r,g,b]
            if (args.threshold != None):
                stats = get_stats(nghbrs_list, int(args.calculate[0]), int(args.threshold[0]));
            else:
                stats = get_stats(nghbrs_list, int(args.calculate[0]));

            # fill the new pxl
            pix_res[i][j] = (int(stats[0]), int(stats[1]), int(stats[2]))

    # Save
    new_img = Image.fromarray(pix_res)
    new_img.save(args.out[0], "JPEG")

    return 0

if __name__ == "__main__":
    main()
