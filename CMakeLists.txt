cmake_minimum_required(VERSION 3.20)

project(LR4)
set(CMAKE_CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)

add_definitions(-D__cpp_concepts=202002L) # magic to make std::expectd compile. Apparently clang's concepts are not ready yet

enable_testing()

include_directories(include)

add_subdirectory(lib/ctoast)
add_subdirectory(Task_1)
add_subdirectory(Task_2)
add_subdirectory(Task_3)
add_subdirectory(lib/googletest)
