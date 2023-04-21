cmake_minimum_required(VERSION 3.10)
project(LexicalTextSimilarity)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

add_executable(LTS main.cpp tokenize.h tokenize.cpp linear.h linear.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(LTS PUBLIC OpenMP::OpenMP_CXX)
endif()
