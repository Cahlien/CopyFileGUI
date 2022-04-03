FROM dc-wxwidgets:latest
MAINTAINER matthew.crowell1@gmail.com
COPY . /code
RUN mkdir ~/.vnc
RUN x11vnc -storepasswd 1234 ~/.vnc/passwd
WORKDIR /code/build/linux/debug
RUN cmake ../../..
RUN make
CMD ["./copyfile"]