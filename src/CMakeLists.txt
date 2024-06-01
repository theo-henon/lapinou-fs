target_sources(lfs PUBLIC
    main.c)

add_subdirectory(utils)
add_subdirectory(volume)
add_subdirectory(io)

target_link_libraries(lfs PRIVATE utils volume io)
