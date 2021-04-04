
cmake_minimum_required(VERSION 3.18)
project(cmg)

set(SOURCE_FILES src/main.cpp)

add_executable(cmg ${SOURCE_FILES})

target_link_libraries(cmg dl fbxsdk)