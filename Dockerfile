# Use an official lightweight C++ image
FROM gcc:latest

# Set environment variables
ENV SERVER_PORT=10000
ENV UI_PORT=8080

# Install required libraries
RUN apt-get update && apt-get install -y cmake make g++ curl unzip

# Create directory for nlohmann/json and install it
RUN mkdir -p /usr/include/nlohmann && \
    curl -L https://github.com/nlohmann/json/releases/latest/download/json.hpp -o /usr/include/nlohmann/json.hpp

# Copy source files
COPY server.cpp /server.cpp
COPY ui.cpp /ui.cpp

# Compile the C++ files
RUN g++ -std=c++17 -o server server.cpp -lssl -lz
RUN g++ -std=c++17 -o ui ui.cpp -lssl -lz

# Expose the correct ports
EXPOSE 10000
EXPOSE 8080

# Run the server
CMD ["./server"]
