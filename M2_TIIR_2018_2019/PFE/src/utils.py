import numpy as np

from const import *


def get_vertical_neighbours(mat, i, j, i_max):
    res = []
    res.append(mat[i,j])

    # TOP
    if (i - 1) >= 0: res.append(mat[i-1,j])

    # DOWN
    if (i + 1) <= i_max: res.append(mat[i+1,j])

    return res

def get_horizontal_neighbours(mat, i, j, j_max):
    res = []
    res.append(mat[i,j])

    # LEFT
    if (j - 1) >= 0: res.append(mat[i,j-1])

    # RIGHT
    if (j + 1) <= j_max: res.append(mat[i,j+1])

    return res

"""
    return the adjacent neighbours 
"""
def get_neighbours(mat, i, j, i_max, j_max):
    res = []
    res.append(mat[i,j])

    # TOP
    if (i - 1) >= 0 and (j - 1) >= 0: res.append(mat[i-1,j-1])
    if (i - 1) >= 0: res.append(mat[i-1,j])
    if (i - 1) >= 0 and (j + 1) <= j_max: res.append(mat[i-1,j+1])

    # LEFT
    if (j - 1) >= 0: res.append(mat[i,j-1])

    # RIGHT
    if (j + 1) <= j_max: res.append(mat[i,j+1])

    # DOWN
    if (i + 1) <= i_max and (j - 1) >= 0: res.append(mat[i+1,j-1])
    if (i + 1) <= i_max: res.append(mat[i+1,j])
    if (i + 1) <= i_max and (j + 1) <= j_max: res.append(mat[i+1,j+1])

    return res

"""
    return array submatrix position
    format: [(x0_min,y0_min),(x1_max,y1_max),.....]
    => reconstitute block:  (x0_min,y0_min),(x0_min,y1_max),
                            (x1_max,y0_min),(x1_max,y1_max)
"""
def get_blocks_pos(edge, i_max, j_max, skip=None):

    #logging.debug("get_blocks_pos: enter with edge = %d, I_MAX = %d, J_MAX = %d, skip = %d " % (edge,i_max, j_max,skip));
    # calculate pos
    res = []
    i1,j1 = 0,0
    for i in range(0,i_max,edge):

        if (skip != None) and (i1 % skip != 0):
            #print("[1] i skip, i1=%d, j1 =%d" % (i1, j1))
            i1 += 1
            continue;

        for j in range(0,j_max,edge):

            if (skip != None) and (j1 % skip != 0):
                #print("[2] i skip, i1=%d, j1 =%d" % (i1,j1))
                j1 += 1
                continue;

            # calculate the max
            tmp_i = i + edge - 1;
            tmp_j = j + edge - 1;
            if (tmp_i <= i_max) and (tmp_j <= j_max):
                res.append((i,j))

                # adjust
                if tmp_i >= i_max:
                    tmp_i -= 1;
                if tmp_j >= j_max:
                    tmp_j -= 1;

                res.append((tmp_i,tmp_j))

            j1 += 1
        i1 += 1
        j1 = 0

    #logging.debug("get_blocks_pos: nb_block = %d " % (len(res)//2));
    return res;

def get_submatrice_asarray(mat, min_pos, max_pos, edge):
    #logging.debug("get_submatrice_asarray: enter with min_pos = %s, max_pos = %s " % (min_pos, max_pos));

    res = []

    for i in range(min_pos[0], max_pos[0]+1):
        for j in range(min_pos[1],max_pos[1]+1):
            res.append(mat[i][j]);

    #logging.debug("get_submatrice_asarray: nb_elem = %d " % len(res));

    return res;

def fill_sub_matrix(mat, min_pos, max_pos, pxl):
    #logging.debug("fill_sub_matrix: enter");

    for i in range(min_pos[0], max_pos[0]+1):
        for j in range(min_pos[1],max_pos[1]+1):
           mat[i][j] = pxl;

    return 0;

