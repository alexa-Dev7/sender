FROM ubuntu:latest
WORKDIR /app

# Install dependencies
RUN apt update && apt install -y build-essential libssl-dev cmake

# Copy all project files to the container
COPY . /app

# Compile the WebSocket server
RUN g++ -std=c++17 -o server server.cpp -luWS -lssl -lz

# Start the server
CMD ["./server"]
