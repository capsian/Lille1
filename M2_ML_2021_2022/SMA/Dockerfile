FROM python:3.8
MAINTAINER Selim Lakhdar <selim.lakhdar@gmail.com>
MAINTAINER Josue Happe <josue.happe.etu@univ-lille.fr>

# install build utilities
RUN apt-get update
RUN apt-get install -y gcc make apt-transport-https ca-certificates build-essential

# update pip
RUN pip3 install --upgrade pip

# set the working directory for containers
RUN mkdir /SMA
WORKDIR  /SMA

# Copy all the files from the project’s root to the working directory
COPY . /SMA

# Installing python dependencies
RUN pip3 install --no-cache-dir -r requirements.txt

# Running Python Application
CMD ["cd src && python3 server.py"]