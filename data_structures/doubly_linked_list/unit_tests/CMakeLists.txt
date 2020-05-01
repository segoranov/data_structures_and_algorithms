cmake_minimum_required(VERSION 3.10)

project(doubly_linked_list_data_structure_unit_tests)

add_executable(run_unit_tests main_utest.cpp doubly_linked_list_utest.cpp)

set_property(TARGET run_unit_tests PROPERTY CXX_STANDARD 17)

target_include_directories( run_unit_tests PUBLIC
    ${CMAKE_SOURCE_DIR}/..
    ${CMAKE_SOURCE_DIR}/../../../unit_test_framework )
