# Use an official lightweight C++ image
FROM gcc:latest

# Set environment variables
ENV SERVER_PORT=10000
ENV UI_PORT=8080

# Install required libraries
RUN apt-get update && apt-get install -y cmake make g++ git

# Install nlohmann/json (JSON library) properly
RUN git clone https://github.com/nlohmann/json.git && \
    cd json && mkdir build && cd build && cmake .. && make && make install && \
    cd ../.. && rm -rf json

# Ensure the library is available
RUN mkdir -p /usr/include/nlohmann && \
    cp /usr/local/include/nlohmann/json.hpp /usr/include/nlohmann/

# Copy source files
COPY server.cpp /server.cpp
COPY ui.cpp /ui.cpp

# Compile the C++ files
RUN g++ -std=c++17 -o server server.cpp -lssl -lz
RUN g++ -std=c++17 -o ui ui.cpp -lssl -lz

# Expose the chat server and UI ports
EXPOSE 10000
EXPOSE 8080

# Run the server
CMD ["./server"]
