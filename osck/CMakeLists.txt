cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(carbon VERSION 1.0)

# All files
file(GLOB_RECURSE kern kern/*.c)
file(GLOB_RECURSE vm vm/*.c)

# Set the compiler to be clang -t x86_64-pc-none-elf
set(triple x86_64-pc-none-elf)
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ${triple})

set(CMAKE_SYSROOT "include")

#configure the linker
set(CMAKE_C_FLAGS "-c -ffreestanding -fshort-wchar -Ofast -pedantic -Wall -Wno-implicit-int -Wno-unknown-pragmas")

# Building
add_library(kernel OBJECT ${kern} ${vm})
include_directories(carbon PUBLIC ../include)