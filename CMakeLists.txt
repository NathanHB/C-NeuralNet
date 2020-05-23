cmake_minimum_required(VERSION 3.17)
project(cpp_neuralNet)

set(CMAKE_CXX_STANDARD 14)

include_directories(matrix)
include_directories(network)
include_directories(parser)

add_executable(cpp_neuralNet
        matrix/matrix.cpp
        matrix/matrix.hpp
        network/network.cpp
        network/network.hpp
        parser/idx_header.cpp
        parser/idx_header.hpp
        main.cpp)

