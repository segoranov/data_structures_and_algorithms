cmake_minimum_required(VERSION 3.10)

project(deque_data_structure)

add_executable(deque_demo deque_demo.cpp)

set_property(TARGET deque_demo PROPERTY CXX_STANDARD 17)

add_subdirectory(unit_tests)
