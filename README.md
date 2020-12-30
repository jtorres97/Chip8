# Chip8
Yet another Chip 8 emulator/interpreter, written in modern C++

## Setup
To get up and running with this project you will need:
* A C++17 compiler
* An installed and properly set up version of [Conan](https://conan.io/)
* A somewhat recent [CMake](https://cmake.org/) version

## Compiling
Before compiling you need to add the bincrafters remote to get the package(s) defined in the conanfile.
```bash
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```
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

## Screenshots
<p align="center">
  <img src="/docs/test_opcode.jpg" width="400" />
  <img src="/docs/pong.jpg" width="400" /> 
</p>
<p align="center">
    <img src="/docs/brix.jpg" width="400" /> 
    <img src="/docs/space_invaders.jpg" width="400" /> 
</p>
