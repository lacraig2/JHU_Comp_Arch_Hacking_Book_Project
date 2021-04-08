FROM ubuntu:20.04
RUN apt update
RUN apt-get -y install gcc-arm-linux-gnueabihf
RUN mkdir /workspace
WORKDIR /workspace