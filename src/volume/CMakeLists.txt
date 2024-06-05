add_library(volume
    file.c file.h
        volume.c
        volume.h)

target_link_libraries(volume PRIVATE utils)

add_subdirectory(tests)