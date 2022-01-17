FROM python:3.8
MAINTAINER Selim Lakhdar <selim.lakhdar@gmail.com>

# install build utilities
RUN apt-get update
RUN apt-get install -y gcc make apt-transport-https ca-certificates build-essential

# update pip
RUN pip3 install --upgrade pip

# set the working directory for containers
RUN mkdir /sentiment_classifier
WORKDIR  /sentiment_classifier

# Copy all the files from the project’s root to the working directory
COPY . /sentiment_classifier

# Installing python dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Install spacy
RUN python3 -m spacy download fr_core_news_lg

# Running Python Application
CMD ["python", "/sentiment_classifier/src/server.py"]