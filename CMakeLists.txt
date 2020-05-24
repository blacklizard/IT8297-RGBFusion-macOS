cmake_minimum_required(VERSION 3.16)

#set(CMAKE_C_COMPILER "/usr/bin/gcc")
#set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(RGBFussion)
set(CMAKE_CXX_STANDARD 14)

find_package (PkgConfig REQUIRED)
pkg_check_modules (HIDAPI REQUIRED hidapi)
include_directories (${HIDAPI_INCLUDE_DIRS})
link_directories (${HIDAPI_LIBRARY_DIRS})

add_executable(RGBFussion main.cpp src/Controller.cpp src/Controller.h src/Effect.cpp src/Effect.h)

add_definitions (${HIDAPI_CFLAGS_OTHER})
target_link_libraries (RGBFussion ${HIDAPI_LIBRARIES})