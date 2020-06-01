cmake_minimum_required(VERSION 3.10)

project(dynamic_array_data_structure_unit_tests)

add_executable(run_dyn_array_non_template_tests main_utest.cpp dynamic_array_utest.cpp ../dynamic_array.cpp)

set_property(TARGET run_dyn_array_non_template_tests PROPERTY CXX_STANDARD 20)

target_include_directories(run_dyn_array_non_template_tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../unit_test_framework )
