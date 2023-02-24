cmake_minimum_required(VERSION 3.24)
project(LexicalTextSimilarity)

set(CMAKE_CXX_STANDARD 20)

add_executable(LexicalTextSimilarity main.cpp  linear.h linear.cpp)
add_executable(LinearTest linear.cpp)
