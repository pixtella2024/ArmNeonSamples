cmake_minimum_required(VERSION 3.1)
SET( CMAKE_CXX_COMPILER clang++ )
project(VecArithSubWidenSub CXX)

set(VecArithSubWidenSub_src
VecArithSubWidenSub.cpp
)

add_executable(VecArithSubWidenSub ${VecArithSubWidenSub_src})

target_compile_options(VecArithSubWidenSub PUBLIC -O3 -march=armv8.2-a)
target_compile_features(VecArithSubWidenSub PUBLIC cxx_std_23)