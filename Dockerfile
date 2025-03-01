FROM ubuntu:latest
WORKDIR /app

RUN apt update && apt install -y build-essential libssl-dev cmake

COPY sender/ /app
WORKDIR /app
RUN g++ -std=c++17 -o server server.cpp -luWS -lssl -lz

CMD ["./server"]
