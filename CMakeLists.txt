cmake_minimum_required(VERSION 3.10)
project(LexicalTextSimilarity)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

add_executable(LexicalTextSimilarity_2dvector main.cpp tokenize.h tokenize.cpp LTS.h LTS_2d.cpp linear_2d.h linear_2d.cpp)
add_executable(LexicalTextSimilarity_flatvector main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_loop_ijk.cpp linear.h linear.cpp)
add_executable(LexicalTextSimilarity_flatvector_loop_ijk main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_loop_ijk.cpp linear.h linear.cpp)
add_executable(LexicalTextSimilarity_flatvector_loop_ikj main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_loop_ikj.cpp linear.h linear.cpp)
add_executable(LexicalTextSimilarity_flatvector_loop_kji main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_loop_kji.cpp linear.h linear.cpp)