# Use Debian as base image
FROM debian:latest

# Install dependencies
RUN apt update && apt install -y g++ cmake make libssl-dev zlib1g-dev git curl pkg-config

# Install nlohmann/json library
RUN apt install -y nlohmann-json3-dev

# Set working directory
WORKDIR /app

# Copy source files
COPY server.cpp ui.cpp messages.json .env ./

# Compile Short Polling server
RUN g++ -std=c++17 -o server server.cpp -lssl -lz

# Compile UI server
RUN g++ -std=c++17 -o ui ui.cpp -lssl -lz -lpthread

# Expose dynamic Render port
EXPOSE 10000

# Load environment variables and start both servers
CMD export $(cat .env | xargs) && ./server
