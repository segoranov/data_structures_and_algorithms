cmake_minimum_required(VERSION 3.10)

project(deque_data_structure_unit_tests)

add_executable(run_deque_tests main_utest.cpp deque_utest.cpp)

set_property(TARGET run_deque_tests PROPERTY CXX_STANDARD 20)

target_include_directories( run_deque_tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../unit_test_framework)
