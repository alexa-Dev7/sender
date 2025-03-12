FROM ubuntu:latest
WORKDIR /app
COPY . .
RUN apt-get update && apt-get install -y g++ cmake
RUN cmake . && make
CMD ["./server"]
