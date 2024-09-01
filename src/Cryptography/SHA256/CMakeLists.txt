cmake_minimum_required(VERSION 3.1)
SET( CMAKE_CXX_COMPILER clang++ )
project(sha256arm CXX)

set(sha256arm_src
    main.cpp
    Sha256.cpp
    Sha256Ref.cpp
    Sha256Neon.cpp
)

add_executable(sha256arm ${sha256arm_src})

target_compile_options(sha256arm PUBLIC -O3 -march=armv8.2-a+sha2)
target_compile_features(sha256arm PUBLIC cxx_std_17)