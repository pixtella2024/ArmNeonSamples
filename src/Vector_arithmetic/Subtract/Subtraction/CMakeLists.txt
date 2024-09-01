cmake_minimum_required(VERSION 3.1)
SET( CMAKE_CXX_COMPILER clang++ )
project(VecArithSubSub CXX)

set(VecArithSubSub_src
    VecArithSubSub.cpp
)

add_executable(VecArithSubSub ${VecArithSubSub_src})

target_compile_options(VecArithSubSub PUBLIC -O3 -march=armv8.2-a)
target_compile_features(VecArithSubSub PUBLIC cxx_std_23)