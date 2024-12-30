cmake_minimum_required(VERSION 3.12)

project(notes LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(SOURCES src/multithreading3.cpp)

include_directories()

add_executable(notes ${SOURCES})

target_compile_options(notes PRIVATE -Wall -Wextra -Werror -Wnrvo)
