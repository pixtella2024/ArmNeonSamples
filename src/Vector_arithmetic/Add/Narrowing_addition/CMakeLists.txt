cmake_minimum_required(VERSION 3.1)
SET( CMAKE_CXX_COMPILER clang++ )
project(VecArithAddNarrowAdd CXX)

set(VecArithAddNarrowAdd_src
    VecArithAddNarrowAdd.cpp
)

add_executable(VecArithAddNarrowAdd ${VecArithAddNarrowAdd_src})

target_compile_options(VecArithAddNarrowAdd PUBLIC -O3 -march=armv8.2-a)
target_compile_features(VecArithAddNarrowAdd PUBLIC cxx_std_23)