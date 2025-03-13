FROM ubuntu:latest
RUN apt-get update && apt-get install -y g++ cmake git libbcrypt-dev
COPY sender /app
WORKDIR /app
RUN cmake . && make
CMD ["./server"]
