# Minimum CMake version
cmake_minimum_required(VERSION 3.9)

# Project name
project(Chip8)

# C++ 17 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Pull in the generated conan cmake
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Add all sources/headers
include_directories(include)
file(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADER_FILES "${PROJECT_SOURCE_DIR}/include/*.h")

# Bundle sources and libs
add_executable(chip8 ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(chip8 ${CONAN_LIBS})