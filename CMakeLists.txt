cmake_minimum_required(VERSION 3.20)
project(lapinou-fs VERSION 1.0 LANGUAGES C)

include_directories(src)


add_subdirectory(lib)
add_executable(lfs)
add_subdirectory(src)