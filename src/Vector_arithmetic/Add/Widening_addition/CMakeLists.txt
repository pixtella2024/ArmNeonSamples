cmake_minimum_required(VERSION 3.1)
SET( CMAKE_CXX_COMPILER clang++ )
project(VecArithAddWidenAdd CXX)

set(VecArithAddWidenAdd_src
VecArithAddWidenAdd.cpp
)

add_executable(VecArithAddWidenAdd ${VecArithAddWidenAdd_src})

target_compile_options(VecArithAddWidenAdd PUBLIC -O3 -march=armv8.2-a)
target_compile_features(VecArithAddWidenAdd PUBLIC cxx_std_23)