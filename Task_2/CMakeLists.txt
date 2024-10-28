cmake_minimum_required(VERSION 3.18)
set(TASK task_2)

add_executable(${TASK} main.cc app.cc)
target_link_libraries(${TASK} PUBLIC ctoast)

add_executable(${TASK}_tests tests.cc app.cc)
target_link_libraries(${TASK}_tests gtest_main)
add_test(NAME ${TASK}_tests COMMAND ${TASK}_tests)