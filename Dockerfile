# ✅ Use a stable Ubuntu version
FROM ubuntu:22.04

# ✅ Install essential packages (g++, cmake, git, OpenSSL for SHA256)
RUN apt-get update && apt-get install -y g++ cmake git ca-certificates libssl-dev make

# ✅ Clone nlohmann/json library
RUN git clone https://github.com/nlohmann/json.git /json

# ✅ Copy the app files
COPY . /app
WORKDIR /app

# ✅ Build the server (now SHA256-friendly)
RUN cmake . && make

# ✅ Set environment variables
ENV TERM=xterm
ENV PORT=8080

# ✅ Expose port for Render
EXPOSE 8080

# ✅ Run the server
CMD ["./server"]
