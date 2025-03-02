# Use an official lightweight C++ image
FROM gcc:latest

# Set environment variables
ENV SERVER_PORT=10000

# Install required libraries
RUN apt-get update && apt-get install -y cmake make g++

# Install nlohmann/json (JSON library)
RUN git clone https://github.com/nlohmann/json.git && \
    cd json && mkdir build && cd build && cmake .. && make && make install

# Copy source files
COPY server.cpp /server.cpp
COPY ui.cpp /ui.cpp

# Compile the C++ files
RUN g++ -std=c++17 -o server server.cpp -lssl -lz
RUN g++ -std=c++17 -o ui ui.cpp -lssl -lz

# Expose the chat server port
EXPOSE 10000

# Run the server
CMD ["./server"]
