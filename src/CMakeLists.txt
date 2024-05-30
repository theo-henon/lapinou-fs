target_sources(lfs PUBLIC
    main.c)

add_subdirectory(files)

target_link_libraries(lfs PRIVATE file)
