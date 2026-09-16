cmake_minimum_required(VERSION 3.20)
project(hangman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(hangman src/main.cpp)

if (MSVC)
    target_compile_options(hangman PRIVATE /W4)
else()
    target_compile_options(hangman PRIVATE -Wall -Wextra -Wpedantic)
endif()
