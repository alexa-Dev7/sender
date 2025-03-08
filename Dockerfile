# Use an official lightweight C++ image
FROM debian:latest

# Set working directory
WORKDIR /app

# Install dependencies
RUN apt-get update && apt-get install -y \
    curl \
    git \
    g++ \
    make \
    cmake \
    libssl-dev \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

# Install nlohmann/json (JSON library)
RUN mkdir -p /usr/include/nlohmann && \
    curl -L https://github.com/nlohmann/json/releases/latest/download/json.hpp -o /usr/include/nlohmann/json.hpp

# Install uWebSockets (required for real-time messaging)
RUN curl -L https://github.com/uNetworking/uWebSockets/archive/refs/tags/v20.44.0.tar.gz -o uwebsockets.tar.gz && \
    tar -xzf uwebsockets.tar.gz && \
    cd uWebSockets-20.44.0 && \
    make && make install && \
    cd .. && rm -rf uwebsockets.tar.gz uWebSockets-20.44.0

# Copy project files into container
COPY sender /app

# Compile the project
RUN g++ -o server sender/server.cpp -std=c++17 -luWS -lssl -lz -pthread

# Expose port
EXPOSE 10000

# Run the server
CMD ["./server"]
