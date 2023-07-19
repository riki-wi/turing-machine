cmake_minimum_required(VERSION 3.16.3)
project(turing_machine)

set(CMAKE_CXX_STANDARD 17)

add_executable(turing_machine main.cpp src/turingmachine.cpp src/turingprogram.cpp
            external/simple-str.cpp)
