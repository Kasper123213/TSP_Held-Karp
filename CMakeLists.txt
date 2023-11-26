cmake_minimum_required(VERSION 3.24)
project(PEA1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(PEA1 main.cpp Test.h Test.cpp time/Time.h time/Time.cpp algoritgms/HeldKarp.h algoritgms/HeldKarp.cpp)

