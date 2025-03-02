# Use Debian as base image
FROM debian:latest

# Install dependencies
RUN apt update && apt install -y g++ cmake make libssl-dev zlib1g-dev git curl pkg-config

# Set working directory
WORKDIR /app

# Copy source files
COPY server.cpp ui.cpp messages.json .env ./

# Compile Short Polling server
RUN g++ -std=c++17 -o server server.cpp -lssl -lz

# Compile UI server
RUN g++ -std=c++17 -o ui ui.cpp -lssl -lz -lpthread

# Expose ports
EXPOSE 9001 8080

# Load environment variables and start both servers
CMD export $(cat .env | xargs) && ./server & ./ui
