cmake_minimum_required(VERSION 3.1)
SET( CMAKE_CXX_COMPILER clang++ )
project(VecArithSubNarrowSub CXX)

set(VecArithSubNarrowSub_src
    VecArithSubNarrowSub.cpp
)

add_executable(VecArithSubNarrowSub ${VecArithSubNarrowSub_src})

target_compile_options(VecArithSubNarrowSub PUBLIC -O3 -march=armv8.2-a)
target_compile_features(VecArithSubNarrowSub PUBLIC cxx_std_23)