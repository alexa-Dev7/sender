# Use Ubuntu 22.04 for stability
FROM ubuntu:22.04

# Install necessary packages (OpenSSL for bcrypt-like hashing)
RUN apt-get update && apt-get install -y g++ cmake git ca-certificates libssl-dev make

# Clone nlohmann/json library
RUN git clone https://github.com/nlohmann/json.git /json

# Copy the app files
COPY . /app
WORKDIR /app

# Build the server
RUN cmake . && make

# Set environment variables
ENV TERM=xterm
ENV PORT=8080

# Expose port for Render to detect
EXPOSE 8080

# Start the server
CMD ["./server"]
