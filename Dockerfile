# Use a base image with C++
FROM gcc:latest

# Set environment variables
ENV SERVER_PORT=9001
ENV UI_PORT=8080

# Install dependencies
RUN apt-get update && apt-get install -y cmake make g++

# Install nlohmann/json
RUN git clone https://github.com/nlohmann/json.git && \
    cd json && mkdir build && cd build && cmake .. && make && make install

# Copy source files
COPY server.cpp /server.cpp
COPY ui.cpp /ui.cpp

# Compile the C++ files
RUN g++ -std=c++17 -o server server.cpp -lssl -lz
RUN g++ -std=c++17 -o ui ui.cpp -lssl -lz

# Expose the ports
EXPOSE 9001
EXPOSE 8080

# Start the server
CMD ["./server"]
