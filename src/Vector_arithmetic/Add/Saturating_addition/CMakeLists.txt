cmake_minimum_required(VERSION 3.1)
SET( CMAKE_CXX_COMPILER clang++ )
project(VecArithAddSatAdd CXX)

set(VecArithAddSatAdd_src
    VecArithAddSatAdd.cpp
)

add_executable(VecArithAddSatAdd ${VecArithAddSatAdd_src})

target_compile_options(VecArithAddSatAdd PUBLIC -O3 -march=armv8.2-a)
target_compile_features(VecArithAddSatAdd PUBLIC cxx_std_23)