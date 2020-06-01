cmake_minimum_required(VERSION 3.10)

project(graph_data_structure_unit_tests)

add_executable(run_graph_tests main_utest.cpp adjacency_list_graph_utest.cpp)
add_executable(run_graph_algorithms_tests main_utest.cpp graph_algorithms_utest.cpp)

set_property(TARGET run_graph_tests PROPERTY CXX_STANDARD 20)
set_property(TARGET run_graph_algorithms_tests PROPERTY CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-ggdb")

target_include_directories( run_graph_tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../unit_test_framework)

target_include_directories( run_graph_algorithms_tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../unit_test_framework)
