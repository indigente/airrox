#
# To build the docker image, run the command:
#
#   docker build -t airrox .
#
# Then, run the container:
#
#   xhost +
#   docker run -ti --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix airrox /bin/bash
#
# Inside the container, compile and run AirroX:
#
#   cd /airrox/source
#   make
#   ./air
#

FROM ubuntu:14.04
MAINTAINER Rodrigo Rocha Gomes e Souza "rodrigo@dcc.ufba.br"

RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y build-essential
RUN apt-get install -y freeglut3 freeglut3-dev
RUN apt-get install -y --no-install-recommends libsdl1.2-dev libsdl-mixer1.2-dev libsdl-net1.2-dev

ADD . /airrox
