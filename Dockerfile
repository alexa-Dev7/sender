# Use an official lightweight C++ image
FROM debian:latest

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ cmake make git \
    libssl-dev zlib1g-dev

# Set working directory
WORKDIR /app

# Clone uWebSockets manually
RUN git clone --recursive https://github.com/uNetworking/uWebSockets.git && \
    cd uWebSockets && mkdir build && cd build && \
    cmake .. && make && make install && \
    cd ../.. && rm -rf uWebSockets

# Copy C++ source files to container
COPY server.cpp /app/server.cpp
COPY ui.cpp /app/ui.cpp
COPY messages.json /app/messages.json
COPY users.json /app/users.json

# Compile the WebSocket server and UI
RUN g++ -std=c++17 -o server server.cpp -luWS -lssl -lz
RUN g++ -std=c++17 -o ui ui.cpp -luWS -lssl -lz

# Expose ports
EXPOSE 10000  # Server port
EXPOSE 8080   # UI port

# Run the server
CMD ["./server"]
