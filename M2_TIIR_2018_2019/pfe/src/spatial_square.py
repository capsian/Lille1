import os, argparse
from PIL import Image
from tqdm import tqdm
import numpy as np

from filters import *
from utils import *
from const import *

def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--input",        nargs=1,   help="input image");
    parser.add_argument("-o", "--out",          nargs=1,   help="output file");
    parser.add_argument("-e", "--edge",         nargs=1,   help="edge size");
    parser.add_argument("-t", "--threshold",    nargs=1,   help="threshold for the calculation");
    parser.add_argument("-c", "--calculate", nargs=1, help="caculate : mean [1] | median [2] | standard variation [3]");
    parser.add_argument("-s", "--skip", nargs=1, help="skip n pixels (for x&y)");

    args = parser.parse_args()

    if (args.input == None) or (args.out == None) or (args.edge == None) or (args.calculate == None):
        print("Error input !")
        exit(1);

    return args

def main():

    args = arg_parser();

    # Read image & get pixels
    pix_in = np.array(Image.open(args.input[0]))

    # init result img (uint8=[0,255])
    pix_res = np.zeros((I_MAX, J_MAX, 3), dtype=np.uint8)

    # Calculate blocks pos with the edge for slicing
    blocks_pos = get_blocks_pos(int(args.edge[0]), I_MAX, J_MAX);

    for i in tqdm(range(0, len(blocks_pos), 2)):

        # get the submatrice from (x_min,y_min)(x_max,y_max)
        sub_matrix = get_submatrice_asarray(pix_in, blocks_pos[i], blocks_pos[i + 1], int(args.edge[0]))

        if (args.threshold != None):
            stats = get_stats(sub_matrix, int(args.calculate[0]), int(args.threshold[0]));
        else:
            stats = get_stats(sub_matrix, int(args.calculate[0]));

        fill_sub_matrix(pix_res, blocks_pos[i], blocks_pos[i + 1], stats);

    # Save
    new_img = Image.fromarray(pix_res)
    new_img.save(args.out[0], "JPEG")

    return 0

if __name__ == "__main__":
    main()
