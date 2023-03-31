cmake_minimum_required(VERSION 3.10)
project(LexicalTextSimilarity)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

add_executable(LexicalTextSimilarity_2dvector main.cpp tokenize.h tokenize.cpp LTS.h LTS_2d.cpp linear_2d.h linear_2d.cpp)
add_executable(LexicalTextSimilarity_flatvector main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_ijk.cpp linear.h linear.cpp)

# Generate executables using different loop orderings during matrix multiplication in a flat data structure
add_executable(LTS_flat_ijk main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_ijk.cpp linear.h linear.cpp)
add_executable(LTS_flat_ikj main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_ikj.cpp linear.h linear.cpp)
add_executable(LTS_flat_jik main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_jik.cpp linear.h linear.cpp)
add_executable(LTS_flat_jki main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_jki.cpp linear.h linear.cpp)
add_executable(LTS_flat_kij main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_kij.cpp linear.h linear.cpp)
add_executable(LTS_flat_kji main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_kji.cpp linear.h linear.cpp)

# Generate executables using various loop orderings with block copy optimization
add_executable(LTS_flat_ijk_bco main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_ijk_bco.cpp linear.h linear.cpp)
add_executable(LTS_flat_ikj_bco main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_ikj_bco.cpp linear.h linear.cpp)
add_executable(LTS_flat_jki_bco main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_jki_bco.cpp linear.h linear.cpp)
add_executable(LTS_flat_jik_bco main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_jik_bco.cpp linear.h linear.cpp)
add_executable(LTS_flat_kji_bco main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_kji_bco.cpp linear.h linear.cpp)
add_executable(LTS_flat_kij_bco main.cpp tokenize.h tokenize.cpp LTS.h LTS_flat_kij_bco.cpp linear.h linear.cpp)
