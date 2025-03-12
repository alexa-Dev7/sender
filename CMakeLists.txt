cmake_minimum_required(VERSION 3.10)
project(ChatApp)

set(CMAKE_CXX_STANDARD 17)

# Include the JSON library
include_directories(/json/single_include)

add_executable(server server.cpp encrypt.cpp utils.cpp)
