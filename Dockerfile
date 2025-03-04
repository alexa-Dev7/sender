# Use an official lightweight C++ image
FROM gcc:latest

# Set environment variables
ENV SERVER_PORT=10000

# Install required libraries
RUN apt-get update && apt-get install -y \
    cmake \
    make \
    g++ \
    git \
    libssl-dev \
    wget

# Install nlohmann/json (Download json.hpp instead of cloning)
RUN mkdir -p /app && cd /app && \
    wget https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp -O json.hpp

# Set working directory
WORKDIR /app

# Copy source files
COPY server.cpp /app/server.cpp
COPY ui.cpp /app/ui.cpp

# Compile the C++ files
RUN g++ -std=c++17 -o server server.cpp -lssl -lz
RUN g++ -std=c++17 -o ui ui.cpp -lssl -lz

# Expose the chat server port
EXPOSE 10000

# Run the server
CMD ["./server"]
