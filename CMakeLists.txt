cmake_minimum_required(VERSION 3.25)

project(uwuifier)

set(CMAKE_CXX_STANDARD 17)

set(source_dir "${PROJECT_SOURCE_DIR}/src/")
set(lib_dir "${PROJECT_SOURCE_DIR}/lib/")

file(GLOB source_files "${source_dir}/*.cpp")
file(GLOB header_files "${source_dir}/*.h")

add_executable(uwuifier main.cpp ${source_files} ${header_files})

install(TARGETS uwuifier RUNTIME DESTINATION bin)
