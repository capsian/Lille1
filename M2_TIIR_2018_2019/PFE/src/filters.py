import statistics
import numpy as np

from const import *

"""
    split rgb in 3 arrays for stats
"""
def get_rgb(pixls):

    r = np.arange(len(pixls))
    g = np.arange(len(pixls))
    b = np.arange(len(pixls))

    k = 0
    for i in pixls:
        r[k] = i[0]
        g[k] = i[1]
        b[k] = i[2]
        k += 1

    return r,g,b


"""
    calculate mean, median and standard deviation of pxls_list
    if threshold != None, 
        if calculate(pxl) > threshold => white pxl
        if calculate(pxl) < threshold => black pxl
"""
def get_stats(pxls_list, mode, threshold=None):

    t = -1 if threshold == None else threshold

    r, g, b = get_rgb(pxls_list)

    # mean
    if (mode == 1):
        if (threshold):
            tmp = round(statistics.mean(r)) + round(statistics.mean(g)) + round(statistics.mean(b))
            tmp = tmp / 3
            r = 255 if tmp > threshold else 0
            g = 255 if tmp > threshold else 0
            b = 255 if tmp > threshold else 0
        else:
            r = round(statistics.mean(r))
            g = round(statistics.mean(g))
            b = round(statistics.mean(b))
    # median
    elif (mode == 2):
        if (threshold):
            tmp = round(statistics.median(r)) + round(statistics.median(g)) + round(statistics.median(b))
            tmp = tmp / 3
            r = 255 if tmp > threshold else 0
            g = 255 if tmp > threshold else 0
            b = 255 if tmp > threshold else 0
        else:
            r = round(statistics.median(r))
            g = round(statistics.median(g))
            b = round(statistics.median(b))
    # standard deviation
    elif (mode == 3):
        if (threshold):
            tmp = (round(statistics.stdev(r)) + round(statistics.stdev(g)) + round(statistics.stdev(b))) / 3
            r = 255 if tmp > threshold else 0
            g = 255 if tmp > threshold else 0
            b = 255 if tmp > threshold else 0
        else:
            r = round(statistics.stdev(r))
            g = round(statistics.stdev(g))
            b = round(statistics.stdev(b))
    # invalid
    else:
        print("get_stats: invalide mode: %s", mode);
        exit(1)

    return [r,g,b]

def get_frequency(mat_pxl):

    freq = np.zeros(256, dtype=np.uint32)

    for i in range(I_MAX):
        for j in range(J_MAX):
            freq[int(mat_pxl[i][j][0])] += 1

    return freq

def get_grayscale_avg(mat_pxl):

    res = np.zeros((I_MAX,J_MAX,3), dtype=np.uint8)

    for i in range(I_MAX):
        for j in range(J_MAX):
            res[i][j][0] = int(mat_pxl[i][j][0]//3 + mat_pxl[i][j][1]//3 + mat_pxl[i][j][2]//3)
            res[i][j][1] = int(mat_pxl[i][j][0]//3 + mat_pxl[i][j][1]//3 + mat_pxl[i][j][2]//3)
            res[i][j][2] = int(mat_pxl[i][j][0]//3 + mat_pxl[i][j][1]//3 + mat_pxl[i][j][2]//3)

    return res

def get_grayscale_lum(mat_pxl):

    res = np.zeros((I_MAX,J_MAX, 3), dtype=np.uint8)

    for i in range(I_MAX):
        for j in range(J_MAX):
            res[i][j][0] = mat_pxl[i][j][0] * 0.3 + mat_pxl[i][j][1] * 0.59 + mat_pxl[i][j][2] * 0.11
            res[i][j][1] = mat_pxl[i][j][0] * 0.3 + mat_pxl[i][j][1] * 0.59 + mat_pxl[i][j][2] * 0.11
            res[i][j][2] = mat_pxl[i][j][0] * 0.3 + mat_pxl[i][j][1] * 0.59 + mat_pxl[i][j][2] * 0.11

    return res


def get_tor(pxls_list):
    if np.mean(pxls_list) >= 127:
        return (255, 255, 255)
    else:
        return (0, 0, 0)
