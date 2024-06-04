add_executable(vector_tests vector_tests.c)
target_link_libraries(vector_tests PRIVATE utils PUBLIC unity)