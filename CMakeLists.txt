cmake_minimum_required(VERSION 3.10)
project(ChatServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(server server.cpp)
target_include_directories(server PUBLIC /json/single_include)
target_link_libraries(server ssl crypto)  # 🔥 Links OpenSSL
