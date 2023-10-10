from PIL import Image
import numpy as np
import argparse
from tqdm import tqdm

from const import *
from filters import *
from utils import *

def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument("-s",  "--soluce",      nargs=1,   help="input soluce img");
    parser.add_argument("-i",  "--i",           nargs=1,   help="input image");
    parser.add_argument("-o",   "--out",        nargs=1,   help="output file");

    args = parser.parse_args()

    if (args.soluce == None) or (args.i == None) or (args.out == None):
        print("Error input !")
        exit(1);

    return args

def main():

    args = arg_parser()

    soluce = Image.open(args.soluce[0])
    img = Image.open(args.i[0])

    pix_sol = np.array(soluce)
    pix_im = np.array(img)

    # init result img (uint8=[0,255])
    pix_res = np.zeros((I_MAX, J_MAX, 3), dtype=np.uint8)

    # stats
    rgb_bg_ok,rgb_bg_ko = 0,0
    rgb_nu_ok,rgb_nu_ko = 0,0
    sol_black, sol_white = 0,0
    img_black, img_white = 0,0
    res_black, res_white = 0,0
    for i in tqdm(range(0, I_MAX )):
        for j in range(0, J_MAX):

            # Binarize
            if pix_sol[i][j][0] != 0 or pix_sol[i][j][0] != 255:
                if pix_sol[i][j][0] >= RGB_THRESHOLD:
                    pix_sol[i][j][0] = 255
                    sol_white += 1
                else:
                    pix_sol[i][j][0] = 0
                    sol_black += 1
            if pix_im[i][j][0] != 0 or pix_im[i][j][0] != 255:
                if pix_im[i][j][0] >= RGB_THRESHOLD:
                    pix_im[i][j][0] = 255
                    img_white += 1
                else:
                    pix_im[i][j][0] = 0
                    img_black += 1

            # catch pxl in the number
            if pix_sol[i][j][0] == 0:

                res_black += 1

                # correct pxl
                if pix_sol[i][j][0] == pix_im[i][j][0]:
                    pix_res[i][j] = RGB_NU_OK
                    rgb_nu_ok += 1
                else:
                    pix_res[i][j] = RGB_NU_KO
                    rgb_nu_ko += 1

            # catch background
            else:

                res_white += 1

                # correct pxl
                if pix_sol[i][j][0] == pix_im[i][j][0]:
                    pix_res[i][j] = RGB_BG_OK
                    rgb_bg_ok += 1
                else:
                    pix_res[i][j] = RGB_BG_KO
                    rgb_bg_ko += 1

    # save
    new_img = Image.fromarray(pix_res)
    new_img.save(args.out[0], "JPEG")

    print("image %s" % args.soluce[0])
    print(" white pxl : %f%% (%d)" % ((sol_white*100)/(I_MAX*J_MAX), sol_white))
    print(" black pxl : %f%% (%d)" % ((sol_black*100)/(I_MAX*J_MAX), sol_black))
    print("image %s" % args.i[0])
    print(" white pxl : %f%% (%d)" % ((img_white*100)/(I_MAX*J_MAX), img_white))
    print(" black pxl : %f%% (%d)" % ((img_black*100)/(I_MAX*J_MAX), img_black))
    print("diff stats for : %s  -and- %s" % (args.soluce[0], args.i[0]) )
    print(" white pxl : %f%% (%d)" % ((res_white * 100) / (I_MAX * J_MAX), res_white))
    print(" black pxl : %f%% (%d)" % ((res_black * 100) / (I_MAX * J_MAX), res_black))
    print(" bg_pxl_ok : %f%% (%d)" % ( (rgb_bg_ok*100)/(I_MAX*J_MAX) ,rgb_bg_ok))
    print(" bg_pxl_ko : %f%% (%d)" % ( (rgb_bg_ko*100)/(I_MAX*J_MAX) ,rgb_bg_ko))
    print(" nu_pxl_ok : %f%% (%d)" % ( (rgb_nu_ok*100)/(I_MAX*J_MAX) ,rgb_nu_ok))
    print(" nu_pxl_ko : %f%% (%d)" % ( (rgb_nu_ko*100)/(I_MAX*J_MAX) ,rgb_nu_ko))

    return 0

if __name__ == "__main__":
    main()
