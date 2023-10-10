import os, argparse
from PIL import Image
from tqdm import tqdm

from filters import *
from utils import *
from const import *


def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-o",   "--output",     nargs=1,    help="output image");
    parser.add_argument("-i",   "--input",      nargs='+',  help="input images list");
    parser.add_argument("-c",   "--calculate",  nargs=1,    help="caculate : mean [1] | median [2] | standard variation [3]");
    parser.add_argument("-e",   "--edge",       nargs=1,    help="edge block length");
    parser.add_argument("-t",   "--threshold",  nargs=1,    help="threshold for the calculation");
    parser.add_argument("-s",   "--skip",       nargs=1,    help="skip n pixels (for x&y)");

    args = parser.parse_args()

    if (args.edge == None) or (args.output == None) or (args.calculate == None) or (args.input == None):
        print("Error input !")
        exit(1);

    return args

def main():

    args = arg_parser();

    # init new imgs
    pix_res = np.zeros((I_MAX, J_MAX, 3), dtype=np.uint8)

    # load imgs
    pxl_list = []
    for i in args.input:
        pxl_list.append(np.array(Image.open(i)))

    # Calculate blocks pos with the edge for slicing
    if args.skip != None :
        blocks_pos = get_blocks_pos(int(args.edge[0]), I_MAX, J_MAX, int(args.skip[0]));
    else:
        blocks_pos = get_blocks_pos(int(args.edge[0]), I_MAX, J_MAX);


    # Construct the new img, block per block
    for i in tqdm(range(0, len(blocks_pos), 2)):

        # get submatrices for each block
        sub_matrix_pxl_list = []
        for elem in pxl_list:
            sub_matrix_pxl_list += get_submatrice_asarray(elem, blocks_pos[i], blocks_pos[i + 1], int(args.edge[0]))

        # calculate stats, return stats=[r,g,b]
        if (args.threshold != None):
            stats = get_stats(sub_matrix_pxl_list, int(args.calculate[0]), int(args.threshold[0]));
        else:
            stats = get_stats(sub_matrix_pxl_list, int(args.calculate[0]));

        fill_sub_matrix(pix_res, blocks_pos[i], blocks_pos[i + 1], stats);

    # Save
    new_img = Image.fromarray(pix_res)
    new_img.save(args.output[0], "JPEG")

    return 0

if __name__ == "__main__":
    main()
