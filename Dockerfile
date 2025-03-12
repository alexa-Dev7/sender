FROM ubuntu:latest

# ✅ Install dependencies
RUN apt-get update && apt-get install -y g++ cmake curl

# ✅ Clone nlohmann/json
RUN git clone https://github.com/nlohmann/json.git /json

# ✅ Set working directory
WORKDIR /app

# ✅ Copy all files
COPY . .

# ✅ Compile the server
RUN cmake . && make

# ✅ Ensure TERM variable is set before starting
CMD ["bash", "-c", "export TERM=xterm-256color && ./server"]
