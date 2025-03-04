# Use an official lightweight C++ image
FROM gcc:latest

# Set environment variables
ENV SERVER_PORT=10000
ENV UI_PORT=8080

# Install required packages
RUN apt-get update && apt-get install -y cmake make g++ git libssl-dev zlib1g-dev

# Clone and build uWebSockets manually
RUN git clone --recursive https://github.com/uNetworking/uWebSockets.git && \
    cd uWebSockets && \
    make && make install && \
    cd .. && rm -rf uWebSockets

# Install nlohmann/json (JSON library)
RUN git clone https://github.com/nlohmann/json.git && \
    cd json && mkdir build && cd build && cmake .. && make && make install

# Copy source files
COPY server.cpp /server.cpp
COPY ui.cpp /ui.cpp

# Compile the C++ files (now linking uWebSockets properly)
RUN g++ -std=c++17 -o server server.cpp -luWS -lssl -lz -lpthread
RUN g++ -std=c++17 -o ui ui.cpp -luWS -lssl -lz -lpthread

# Expose the correct ports for server and UI
EXPOSE 10000
EXPOSE 8080

# Run the server and UI
CMD ./server & ./ui
