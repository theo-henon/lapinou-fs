target_sources(lfs PUBLIC
    main.c)

add_subdirectory(volume)

target_link_libraries(lfs PRIVATE file)
