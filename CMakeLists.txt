cmake_minimum_required(VERSION 3.0)

project(uwuifier)

SET(CMAKE_CXX_COMPILER g++)

set (source_dir "${PROJECT_SOURCE_DIR}/src/")
file(GLOB source_files "${source_dir}/*.cpp")

add_executable(uwuifier ${source_files})

install(TARGETS uwuifier RUNTIME DESTINATION bin)
