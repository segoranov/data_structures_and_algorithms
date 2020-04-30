cmake_minimum_required(VERSION 3.10)

project(dynamic_array_data_structure)

add_executable(run_unit_tests main_utest.cpp dynamic_array_utest.cpp ../dynamic_array.cpp)

set_property(TARGET run_unit_tests PROPERTY CXX_STANDARD 17)

target_include_directories( run_unit_tests PUBLIC ${CMAKE_SOURCE_DIR}/.. )
