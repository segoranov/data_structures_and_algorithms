cmake_minimum_required(VERSION 3.0.0)
project(data_structures_and_algorithms VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(data_structures/binary_search_tree)
add_subdirectory(data_structures/doubly_linked_list)
add_subdirectory(data_structures/dynamic_array_non_template)
add_subdirectory(data_structures/dynamic_array_template)
add_subdirectory(data_structures/stack)

add_test(NAME doubly_linked_list_tests COMMAND run_doubly_linked_list_tests)
