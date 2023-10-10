import os

root_path = "./data/images/"
img_dirs = ["VID_20220208_150059", 'VID_20220208_160639', 'VID_20220225_143730', 'VID_20220225_162342',
            '2022-02-15-153646', '2022-02-15-153851', '2022-02-15-154017', '2022-02-15-154638', '2022-02-25-171209',
            'drones_labels', 'last']

train_file = "./data/train.txt"
test_file = "./data/val.txt"
relatif_path = './images/'

with open(train_file, "w") as trn_file:
    with open(test_file, "w") as tst_file:
        for img_dir in img_dirs:
            for root_dir, directories, files in os.walk(root_path + img_dir):
                for f in files:
                    img_path = relatif_path + img_dir + '/' + f
                    if str(img_path).endswith('jpg'):
                        print(img_path)
                        trn_file.writelines(img_path + '\n')
                        tst_file.writelines(img_path + '\n')
