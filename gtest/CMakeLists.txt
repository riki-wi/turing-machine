cmake_minimum_required(VERSION 3.20)
project(gtest)

set(CMAKE_CXX_STANDARD 17)

include_directories(../ ../external/gtest/googletest ../external/gtest/googletest/include)

add_executable(test mainTest.cpp ../external/gtest/googletest/src/gtest-all.cc ../src/turingprogram.cpp
               ../src/turingmachine.cpp ../external/simple-str.cpp)