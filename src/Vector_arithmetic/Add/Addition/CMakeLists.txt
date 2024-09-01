cmake_minimum_required(VERSION 3.1)
SET( CMAKE_CXX_COMPILER clang++ )
project(VecArithAddAdd CXX)

set(VecArithAddAdd_src
    VecArithAddAdd.cpp
)

add_executable(VecArithAddAdd ${VecArithAddAdd_src})

target_compile_options(VecArithAddAdd PUBLIC -O3 -march=armv8.2-a)
target_compile_features(VecArithAddAdd PUBLIC cxx_std_23)