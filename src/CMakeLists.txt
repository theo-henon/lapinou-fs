target_sources(lfs PUBLIC
    main.c)

add_subdirectory(file)

target_link_libraries(lfs PRIVATE file)
