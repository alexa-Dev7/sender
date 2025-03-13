FROM ubuntu:latest

# ✅ Update, install dependencies, and make sure git is included
RUN apt-get update && apt-get install -y g++ cmake git ca-certificates

# ✅ Clone nlohmann/json (now git will work!)
RUN git clone https://github.com/nlohmann/json.git /json

# ✅ Copy the source files into the container
COPY . /app
WORKDIR /app

# ✅ Build the C++ server
RUN cmake . && make

# ✅ Set environment variables
ENV TERM=xterm  
ENV PORT=9001

# ✅ Start the server
CMD ["./server"]
