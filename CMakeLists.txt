cmake_minimum_required(VERSION 3.18)

project(LR4)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(include)

add_subdirectory(lib/ctoast)
add_subdirectory(Task_1)
add_subdirectory(lib/googletest)
