# Use Debian as base image
FROM debian:latest

# Install dependencies
RUN apt update && apt install -y g++ cmake make libssl-dev zlib1g-dev git curl pkg-config

# Copy source files
COPY server.cpp /server.cpp
COPY ui.cpp /ui.cpp
COPY messages.json /messages.json

# Compile Short Polling server
RUN g++ -std=c++17 -o server server.cpp -lssl -lz

# Compile UI server
RUN g++ -std=c++17 -o ui ui.cpp -lssl -lz -lpthread

# Expose ports
EXPOSE 9001 8080

# Run both servers
CMD ./server & ./ui
