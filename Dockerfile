FROM ubuntu:latest
WORKDIR /app

# Install required dependencies
RUN apt update && apt install -y \
    build-essential \
    libssl-dev \
    cmake \
    git \
    wget \
    zlib1g-dev

# Install uWebSockets correctly
RUN git clone https://github.com/uNetworking/uWebSockets.git && \
    cd uWebSockets && \
    git submodule update --init && \
    mkdir build && cd build && \
    cmake .. && make -j$(nproc) && make install && \
    cd ../.. && rm -rf uWebSockets

# Install JSON & bcrypt dependencies
RUN wget https://github.com/nlohmann/json/releases/latest/download/json.hpp -O /usr/include/json.hpp
RUN git clone https://github.com/nieksand/bcrypt.git && \
    cd bcrypt && \
    make && cp bcrypt.a /usr/local/lib && \
    cp bcrypt.hpp /usr/local/include && \
    cd .. && rm -rf bcrypt

# Copy all project files to the container
COPY . /app

# Compile the WebSocket server
RUN g++ -std=c++17 -o server server.cpp -luWS -lssl -lz -lbcrypt -lpthread

# Expose the Render port
EXPOSE 10000

# Start the server
CMD ["./server"]
