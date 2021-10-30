cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(libkern VERSION 1.0)

# All files
file(GLOB_RECURSE libkern ./*.c)

# Set the compiler to be clang -t x86_64-pc-none-elf
set(triple x86_64-pc-none-elf)
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ${triple})

set(CMAKE_SYSROOT "include")

#configure the linker
set(CMAKE_C_FLAGS "-c -ffreestanding -fshort-wchar -Ofast -pedantic -Wall -Wno-implicit-int")

# Building
add_library(libkern OBJECT ${libkern})
include_directories(libkern PUBLIC ../include)