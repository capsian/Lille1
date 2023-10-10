import os
import shutil

vid = "VID_20220225_162342"
img_path = "./data/images/" + vid
labels_path = "./data/labels/" + vid

for r, dirs, files in os.walk(img_path):
    for f in files:
        if f.endswith('.txt'):
            print(f)
            shutil.copy(img_path + "/" + f, labels_path + "/" + f)
            # shutil.copy(img_path + "/" + f.replace('.txt', '.jpg'), labels_path + "/" + f.replace('.txt', '.jpg'))