cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
set(ARCH "i386")

project(Carbon VERSION 0.1 LANGUAGES ASM C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-T${CMAKE_SOURCE_DIR}/aconf/linker.ld")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -pipe")

add_compile_definitions(__debug__)
add_compile_definitions(__kernel__)

include_directories("${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/sys/${ARCH}" "${CMAKE_SOURCE_DIR}/libkern" "${CMAKE_SOURCE_DIR}/libc")

# libraries
add_subdirectory("${CMAKE_SOURCE_DIR}/libkern")
add_subdirectory("${CMAKE_SOURCE_DIR}/libc")

file(GLOB_RECURSE CHIPS "${CMAKE_SOURCE_DIR}/chips/*.c")
file(GLOB_RECURSE DEVICE "${CMAKE_SOURCE_DIR}/device/*.c")
file(GLOB_RECURSE ARCH_S "${CMAKE_SOURCE_DIR}/${ARCH}/*.S")
file(GLOB_RECURSE IPC "${CMAKE_SOURCE_DIR}/ipc/*.c")
file(GLOB_RECURSE KERN "${CMAKE_SOURCE_DIR}/kern/*.c")
file(GLOB_RECURSE UTIL "${CMAKE_SOURCE_DIR}/util/*.c")
file(GLOB_RECURSE VM "${CMAKE_SOURCE_DIR}/vm/*.c")

add_executable(c_kernel ${CHIPS} ${DEVICE} ${ARCH_S} ${IPC} ${KERN} ${UTIL} ${VM})
target_link_libraries(c_kernel PUBLIC kern c)
set_target_properties(c_kernel PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/aconf/linker.ld)