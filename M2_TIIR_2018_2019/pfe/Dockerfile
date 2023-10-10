FROM ubuntu:18.04

# ARG is not persistent in the image ...
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y apt-utils git python3 python3-dev python3-pip python3-tk python3-numpy python3-matplotlib pkg-config libsm6 libxext6 libxrender-dev

# Install dependencies
RUN pip3 install Pillow tqdm numpy matplotlib argparse opencv-python mahotas

#ENTRYPOINT ["docker_entry_point.sh"]