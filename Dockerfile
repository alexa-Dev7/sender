FROM ubuntu:latest

# Install dependencies
RUN apt-get update && apt-get install -y g++ cmake git libbcrypt-dev

# Ensure the /app directory exists
WORKDIR /app

# Copy only necessary files
COPY sender /app/sender

# Set the working directory to the copied files
WORKDIR /app/sender

# Build the C++ server
RUN cmake . && make

# Expose port
EXPOSE 9001

# Start the server
CMD ["./server"]
