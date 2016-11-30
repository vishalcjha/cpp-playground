FROM debian

RUN apt-get update && apt-get -y upgrade

RUN apt-get install --fix-missing -y \
build-essential \
wget \
python \
python-dev \
python-distribute \
python-pip \
libbz2-dev \
zlib1g-dev \
curl \
apache2-utils \
gdb

RUN apt-get install -y cmake

RUN pip install  nose

# Create volume
VOLUME ["/apps/networking"]

# Working directory
WORKDIR /apps/networking
EXPOSE 9999
ENV LD_LIBRARY_PATH=/apps/networking/thirdparty/boost/lib/

# Entrypoint
ENTRYPOINT bash -c "/bin/bash"
