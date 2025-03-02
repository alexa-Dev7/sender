# Use Debian as base image
FROM debian:latest

# Update and install dependencies
RUN apt update && apt install -y \
    g++ cmake make libssl-dev zlib1g-dev git curl pkg-config

# Install uWebSockets from source
RUN git clone --recursive https://github.com/uNetworking/uWebSockets.git && \
    cd uWebSockets && mkdir build && cd build && \
    cmake .. && make && make install && \
    cd ../.. && rm -rf uWebSockets

# Ensure users.json exists before copying
RUN touch users.json

# Copy source files
COPY server.cpp /server.cpp
COPY ui.cpp /ui.cpp
COPY users.json /users.json

# Compile WebSocket server
RUN g++ -std=c++17 -o server server.cpp -luWS -lssl -lz

# Compile UI server
RUN g++ -std=c++17 -o ui ui.cpp -I/usr/local/include -L/usr/local/lib -lcrow -lssl -lz -lpthread

# Expose necessary ports
EXPOSE 9001 8080

# Start both servers
CMD ./server & ./ui
