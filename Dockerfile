# Use Ubuntu
FROM ubuntu:latest

# Install necessary packages
RUN apt-get update && apt-get install -y g++ cmake git ca-certificates libbcrypt-dev

# Clone nlohmann/json library
RUN git clone https://github.com/nlohmann/json.git /json

# Copy app code
COPY . /app
WORKDIR /app

# Build the project
RUN cmake . && make

# Set environment variables
ENV TERM=xterm
ENV PORT=8080

# Expose port for Render to detect
EXPOSE 8080

# Run the server
CMD ["./server"]
