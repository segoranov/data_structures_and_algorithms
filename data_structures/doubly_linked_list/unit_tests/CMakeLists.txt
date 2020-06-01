cmake_minimum_required(VERSION 3.10)

project(doubly_linked_list_data_structure_unit_tests)

set(CMAKE_BUILD_TYPE DEBUG)

add_executable(run_doubly_linked_list_tests main_utest.cpp doubly_linked_list_utest.cpp)

set_property(TARGET run_doubly_linked_list_tests PROPERTY CXX_STANDARD 20)

target_include_directories( run_doubly_linked_list_tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../unit_test_framework )
