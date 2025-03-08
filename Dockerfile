# Use an official C++ image
FROM debian:latest

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    curl \
    libssl-dev \
    zlib1g-dev

# Install uWebSockets (required for real-time messaging)
RUN curl -L https://github.com/uNetworking/uWebSockets/archive/refs/tags/v20.44.0.tar.gz -o uwebsockets.tar.gz && \
    tar -xzf uwebsockets.tar.gz && \
    cd uWebSockets-20.44.0 && \
    make && make install && \
    cd .. && rm -rf uwebsockets.tar.gz uWebSockets-20.44.0

# Install nlohmann/json (JSON library)
RUN curl -L https://github.com/nlohmann/json/releases/latest/download/json.hpp -o /usr/include/nlohmann/json.hpp

# Copy source files
COPY server.cpp /app/server.cpp
COPY ui.cpp /app/ui.cpp
WORKDIR /app

# Compile the C++ files
RUN g++ -std=c++17 -o server server.cpp -luWS -lssl -lz
RUN g++ -std=c++17 -o ui ui.cpp -luWS -lssl -lz

# Expose correct port for Render
EXPOSE 10000

# Run the server
CMD ["./server"]
