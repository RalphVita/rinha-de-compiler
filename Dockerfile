FROM gcc:11.3.0

RUN apt update && \
    apt install -y cmake

WORKDIR /rinha-compiler
COPY . /rinha-compiler
WORKDIR /rinha-compiler/build
#RUN cmake ..  && \
#    make

#ENTRYPOINT ["./main", "/var/rinha/source.rinha.json"]