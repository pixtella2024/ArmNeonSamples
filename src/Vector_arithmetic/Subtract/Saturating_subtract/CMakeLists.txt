cmake_minimum_required(VERSION 3.1)
SET( CMAKE_CXX_COMPILER clang++ )
project(VecArithSubSatSub CXX)

set(VecArithSubSatSub_src
    VecArithSubSatSub.cpp
)

add_executable(VecArithSubSatSub ${VecArithSubSatSub_src})

target_compile_options(VecArithSubSatSub PUBLIC -O3 -march=armv8.2-a)
target_compile_features(VecArithSubSatSub PUBLIC cxx_std_23)