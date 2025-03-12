FROM ubuntu:latest
WORKDIR /app

# Install dependencies
RUN apt-get update && apt-get install -y g++ cmake git

# Get the JSON library
RUN git clone https://github.com/nlohmann/json.git /json

# Copy everything and build
COPY . .
RUN cmake . && make

# Expose the port Render will bind to
EXPOSE 8080

# Start the server
CMD ["./server"]
