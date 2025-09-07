cmake_minimum_required(VERSION 3.20)

project(sha-3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_executable(sha3 examples/multi_mode.cc)

add_executable(sha3_512 examples/single_mode.cc)
target_compile_options(sha3_512 PRIVATE -DSHA_3_512)

add_executable(sha3_256 examples/single_mode.cc)
target_compile_options(sha3_256 PRIVATE -DSHA_3_256)

add_executable(sha3_384 examples/single_mode.cc)
target_compile_options(sha3_384 PRIVATE -DSHA_3_384)

add_executable(sha3_224 examples/single_mode.cc)
target_compile_options(sha3_224 PRIVATE -DSHA_3_224)


add_executable(chunked_sha3_512 examples/chunked.cc)
target_compile_options(chunked_sha3_512 PRIVATE -DSHA_3_512)

add_executable(chunked_sha3_256 examples/chunked.cc)
target_compile_options(chunked_sha3_256 PRIVATE -DSHA_3_256)

add_executable(chunked_sha3_384 examples/chunked.cc)
target_compile_options(chunked_sha3_384 PRIVATE -DSHA_3_384)

add_executable(chunked_sha3_224 examples/chunked.cc)
target_compile_options(chunked_sha3_224 PRIVATE -DSHA_3_224)

enable_testing()
add_executable(sha3_test test/sha3_test.cc)
add_test(NAME sha3_test COMMAND sha3_test)

set(TARGETS chunked_sha3_224 chunked_sha3_384 chunked_sha3_256 chunked_sha3_512
    sha3 sha3_512 sha3_256 sha3_384 sha3_224 sha3_test)

foreach(target IN LISTS TARGETS)
    target_compile_options(${target} PRIVATE
        -std=c++20
        -O3 -Ofast
        -march=native
        -mtune=native
        -flto
        -fno-exceptions
        -fno-rtti
        -nostdlib
        -Wno-shift-count-overflow
    )

    target_include_directories(${target} PRIVATE include/)
endforeach()

