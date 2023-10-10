#!/usr/bin/env bash

echo "Hello !!"
echo "We will steup a new dev-user for our container !"
read -p " username : " username

adduser $username

echo "Well ! we will test our scripts now !!"

src_diff="/dev-env/src/diff.py"
src_freq="/dev-env/src/frequency.py"
src_hist="/dev-env/src/histogram.py"
src_tmpx="/dev-env/src/temporal_px.py"
src_tmsq="/dev-env/src/temporal_square.py"
src_tmck="/dev-env/src/temporal_px_checkerboard.py"
src_tor="/dev-env/src/tor.py"
src_torsq="/dev-env/src/tor_square.py"
src_otsu="/dev-env/src/otsu.py"

input="/dev-env/clear/screens/IMG_00001.bmp /dev-env/clear/screens/IMG_00002.bmp"
sol1="/dev-env/clear/Soluce1.jpg"
sol2="/dev-env/clear/Soluce2.jpg"
out="/dev-env/out"

# FIX ME
#su $username

mkdir -p out

python3 $src_tmpx -i $input -c 3 -o $out/img_1_2_std.jpg
python3 $src_freq -i $out/img_1_2_std.jpg -o $out/img_1_2_std_freq.png
python3 $src_hist -i $out/img_1_2_std.jpg -o $out/img_1_2_std_hist.png
python3 $src_otsu -i $out/img_1_2_std.jpg

python3 $src_tmpx -i $input -c 3 -t 41 -o $out/img_1_2_std_t41.jpg
python3 $src_tmsq -i $input -c 3 -t 41 -e 2 -o $out/img_1_2_std_t41_e2.jpg
python3 $src_tmck -i $input -c 3 -t 41 -o $out/img_1_2_std_t41_chk.jpg

python3 $src_tor -i $out/img_1_2_std_t41.jpg -m 0 -o $out/img_1_2_std_t41_torInv.jpg
python3 $src_tor -i $out/img_1_2_std_t41.jpg -m 1 -t 1 -o $out/img_1_2_std_t41_tor.jpg
python3 $src_tor -i $out/img_1_2_std_t41.jpg -m 2 -t 1 -o $out/img_1_2_std_t41_torV.jpg
python3 $src_tor -i $out/img_1_2_std_t41.jpg -m 3 -t 1 -o $out/img_1_2_std_t41_torH.jpg

python3 $src_torsq -i $out/img_1_2_std_t41.jpg -e 2 -t 1 -o $out/img_1_2_std_t41_torE2.jpg

python3 $src_tmpx -i $sol1 $sol2 -c 1 -o $out/soluce_1_2_mean.jpg
python3 $src_diff -s $out/soluce_1_2_mean.jpg -i $out/img_1_2_std_t41_torE2.jpg -o $out/diff.jpg

chown $username:$username -R $out