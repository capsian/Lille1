import os
import cv2

vid_path = "./data/videos/"
vid = "2022-02-25-171209"
vid_ext = ".webm"

output_path = "./data/images/" + vid + "/"
try:
    os.makedirs(output_path)
except:
    print('Error output directory !')
    os.exit(1)

vidcap = cv2.VideoCapture(vid_path + vid + vid_ext)
success, image = vidcap.read()
count = 0

while success:
    resize = cv2.resize(image, (1280, 720))
    output_name = output_path + str(count) + ".jpg"
    cv2.imwrite(output_name, resize)
    success, image = vidcap.read()
    count += 1
    print(output_name)