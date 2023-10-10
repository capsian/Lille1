import os, argparse
from tqdm import tqdm
from PIL import Image
import numpy as np

from filters import *
from utils import *
from const import *


def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--input", nargs=1, help="input image");
    parser.add_argument("-o", "--out", nargs=1, help="output file");
    parser.add_argument("-t", "--times", nargs=1, help="apply n times");
    parser.add_argument("-e", "--edge", nargs=1, help="square edge size");

    args = parser.parse_args()

    if (args.input == None) or (args.out == None) or (args.times == None) or (args.edge == None):
        print("Error input !")
        exit(1);

    return args


def main():
    args = arg_parser()

    # Read image & get pixels
    pix_in = np.array(Image.open(args.input[0]))

    # init result img (uint8=[0,255])
    pix_res = np.zeros((I_MAX, J_MAX, 3), dtype=np.uint8)

    # Calculate blocks pos with the edge for slicing
    blocks_pos = get_blocks_pos(int(args.edge[0]), I_MAX, J_MAX);

    for k in tqdm(range(int(args.times[0]))):
        for i in range(0, len(blocks_pos), 2):

            if k != 0:
                sub_matrix = get_submatrice_asarray(pix_res, blocks_pos[i], blocks_pos[i + 1], int(args.edge[0]))
            else:
                sub_matrix = get_submatrice_asarray(pix_in, blocks_pos[i], blocks_pos[i + 1], int(args.edge[0]))

            stats = get_tor(sub_matrix);

            fill_sub_matrix(pix_res, blocks_pos[i], blocks_pos[i + 1], stats);

    # Save
    new_img = Image.fromarray(pix_res)
    new_img.save(args.out[0], "PNG")

    return 0


if __name__ == "__main__":
    main()
