cmake_minimum_required(VERSION 3.10)

project(graph_data_structure)

add_executable(graph_demo graph_demo.cpp)

set_property(TARGET graph_demo PROPERTY CXX_STANDARD 17)

add_subdirectory(unit_tests)
