cmake_minimum_required(VERSION 3.10)

project(stack_data_structure_unit_tests)

add_executable(run_stack_tests main_utest.cpp stack_dynamic_array_utest.cpp)

set_property(TARGET run_stack_tests PROPERTY CXX_STANDARD 17)

target_include_directories( run_stack_tests PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../unit_test_framework)
