cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sha3tool_no_optimized sha3.cc example.cc)
add_executable(sha3tool sha3.cc example.cc)

target_compile_options(sha3tool PRIVATE
    -std=c++20
    -O3
    -Ofast
    -ffast-math
    -s
    -march=native
    -flto
    -fno-exceptions
    -fno-rtti
    -funsafe-math-optimizations
    -mavx2
    -msse2
    -m64
    -mprefer-vector-width=256
    -fprefetch-loop-arrays
    -fno-semantic-interposition
    -funroll-loops
)
