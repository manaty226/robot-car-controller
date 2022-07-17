FROM ros:melodic

WORKDIR /usr/local

RUN apt update && apt upgrade -y
RUN apt install -y python-catkin-tools \
        ros-melodic-image-transport \
        ros-melodic-cv-bridge

# installing jpeg-streamer
RUN git clone https://github.com/nadjieb/cpp-mjpeg-streamer.git
WORKDIR /usr/local/cpp-mjpeg-streamer
RUN cmake . && make install


WORKDIR /usr/local
RUN rm -rf /usr/local/cpp-mjpeg-streamer

