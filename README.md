# Chip 8
Yet another Chip 8 emulator/interpreter, written in modern C++

## Setup
To get up and running with this project you will need:
* A C++17 compiler
* An installed and properly set up version of [Conan](https://conan.io/)
* A somewhat recent [CMake](https://cmake.org/) version

## Compiling
Compiling this project is straight forward since there is a single CMake project in this repository.
### MSVC
```bash
mkdir build
cd build
conan install .. -s build_type=Debug --build=missing
conan install .. -s build_type=Release --build=missing
cmake ..
cmake --build . --config <CONFIG>
```
and replace `<CONFIG>` with the configuration you want, either `Debug` or `Release`.

### GCC/Clang (Unix makefiles)
```bash
mkdir build
cd build
conan install .. -s build_type=Debug --build=missing
conan install .. -s build_type=Release --build=missing
cmake .. -DCMAKE_BUILD_TYPE=<CONFIG>
cmake --build .
```
and replace `<CONFIG>` with the configuration you want, either `Debug` or `Release`.
