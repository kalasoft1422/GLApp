cmake_minimum_required(VERSION 3.10.2)

add_subdirectory(Scenes ./scenes)
add_library(glapp STATIC GLApplication.cpp STBDecoder.cpp)

target_link_libraries(glapp scenes)