# Use Debian as base image
FROM debian:latest

# Update package lists and install necessary dependencies
RUN apt update && apt install -y \
    g++ cmake make libssl-dev zlib1g-dev git curl

# Install uWebSockets (for WebSocket server)
RUN git clone https://github.com/uNetworking/uWebSockets && \
    cd uWebSockets && make && make install && \
    cd .. && rm -rf uWebSockets

# Install Crow (for web UI in C++)
RUN git clone --recursive https://github.com/ipkn/crow.git && \
    cd crow && mkdir build && cd build && cmake .. && make && \
    cd ../.. && rm -rf crow

# Copy C++ source files to container
COPY server.cpp /server.cpp
COPY UI.cpp /UI.cpp

# Compile the WebSocket server
RUN g++ -std=c++17 -o server server.cpp -luWS -lssl -lz

# Compile the UI server
RUN g++ -std=c++17 -o ui UI.cpp -I/usr/local/include -L/usr/local/lib -lcrow -lssl -lz -lpthread

# Expose necessary ports
EXPOSE 9001 8080

# Start both servers
CMD ./server & ./ui
