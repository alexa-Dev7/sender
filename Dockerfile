FROM ubuntu:latest

# Install C++ compiler, CMake, and dependencies
RUN apt-get update && apt-get install -y g++ cmake git

# Install nlohmann JSON library via Git
RUN git clone https://github.com/nlohmann/json.git /json

# Set working directory
WORKDIR /app

# Copy project files
COPY . .

# Compile project
RUN cmake . && make

# Run server
CMD ["./server"]
