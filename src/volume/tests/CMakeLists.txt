add_executable(file_tests file_tests.c)
target_link_libraries(file_tests PRIVATE volume PUBLIC unity)