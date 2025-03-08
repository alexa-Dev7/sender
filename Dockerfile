# Use an official C++ image
FROM debian:latest

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    curl \
    libssl-dev \
    zlib1g-dev

# Install nlohmann/json (JSON library)
RUN curl -L https://github.com/nlohmann/json/releases/latest/download/json.hpp -o /usr/include/nlohmann/json.hpp

# Create an app directory
WORKDIR /app

# Copy source files
COPY server.cpp /app/server.cpp
COPY ui.cpp /app/ui.cpp

# Compile the C++ files
RUN g++ -std=c++17 -o server server.cpp -lssl -lz
RUN g++ -std=c++17 -o ui ui.cpp -lssl -lz

# Expose correct port for Render
EXPOSE 10000

# Run the server
CMD ["./server"]
