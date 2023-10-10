import argparse, os
from PIL import Image
from tqdm import tqdm
import hashlib

from const import *
from filters import *
from utils import *


def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i",   "--input",      nargs=1,   help="input image");
    parser.add_argument("-o",   "--out",        nargs=1,   help="output file");
    parser.add_argument("-t",   "--times",      nargs=1,   help="nb iteration");
    parser.add_argument("-m",   "--mode",       nargs=1,   help="mode: 0 reach invariance | 1 get_neighbours | 2 get_vertical_neighbours | 3 get_horizontal_neighbours");

    args = parser.parse_args()

    if (args.input == None) or (args.out == None) or (args.mode == None):
        print("Error input !")
        exit(1);

    return args

def main():

    args = arg_parser()

    # Read image & get pixels
    pix_in = np.array(Image.open(args.input[0]))

    # init result img (uint8=[0,255])
    pix_res = np.zeros((I_MAX, J_MAX, 3), dtype=np.uint8)

    # construct new img pixel per pixel
    # mode get_neighbours
    first = 0
    last_h = hashlib.md5(pix_res).digest()
    if int(args.mode[0]) == 0:
        while (True):
            for i in range(0, I_MAX):
                for j in range(0, J_MAX):
                    if first == 0:
                        neighbours = get_neighbours(pix_in, i, j, I_MAX - 1, J_MAX - 1)
                    else:
                        neighbours = get_neighbours(pix_res, i, j, I_MAX - 1, J_MAX - 1)

                    # calculate, return [r,g,b]
                    stats = get_tor(neighbours)

                    # fill the new pxl
                    pix_res[i][j] = (int(stats[0]), int(stats[1]), int(stats[2]))

            first += 1
            curr_h = hashlib.md5(pix_res).digest()

            if last_h != curr_h:
                last_h = curr_h
            else:
                print("iterated %d times !!" % first)
                break;
    if int(args.mode[0]) == 1:
        for k in tqdm(range(int(args.times[0]))):
            for i in range(0, I_MAX):
                for j in range(0, J_MAX):

                    if k == 0:
                        neighbours = get_neighbours(pix_in, i, j, I_MAX - 1, J_MAX - 1)
                    else:
                        neighbours = get_neighbours(pix_res, i, j, I_MAX - 1, J_MAX - 1)

                    # calculate, return [r,g,b]
                    stats = get_tor(neighbours)

                    # fill the new pxl
                    pix_res[i][j] = (int(stats[0]), int(stats[1]), int(stats[2]))
    # mode get_vertical_neighbours
    elif int(args.mode[0]) == 2:
        for k in tqdm(range(int(args.times[0]))):
            for i in range(0, I_MAX ):
                for j in range(0, J_MAX):

                    if k != 0:
                        neighbours = get_vertical_neighbours(pix_res, i, j, I_MAX - 1)
                    else:
                        neighbours = get_vertical_neighbours(pix_in, i, j, I_MAX - 1)

                    # calculate, return [r,g,b]
                    stats = get_tor(neighbours)

                    # fill the new pxl
                    pix_res[i][j] = (int(stats[0]), int(stats[1]), int(stats[2]))
    # mode get_horizontal_neighbours
    elif int(args.mode[0]) == 3:
        for k in tqdm(range(int(args.times[0]))):
            for i in range(0, I_MAX - 1):
                for j in range(0, J_MAX - 1):

                    if k != 0:
                        neighbours = get_horizontal_neighbours(pix_res, i, j, J_MAX - 1)
                    else:
                        neighbours = get_horizontal_neighbours(pix_in, i, j, J_MAX - 1)

                    # calculate, return [r,g,b]
                    stats = get_tor(neighbours)

                    # fill the new pxl
                    pix_res[i][j] = (int(stats[0]), int(stats[1]), int(stats[2]))
    else:
        print("MODE ERROR !!!")


    # Save
    new_img = Image.fromarray(pix_res)
    new_img.save(args.out[0], "JPEG")

    return 0

if __name__ == "__main__":
    main()
