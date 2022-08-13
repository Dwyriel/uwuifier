cmake_minimum_required(VERSION 3.1)

project(uwuifier)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)

set(source_dir "${PROJECT_SOURCE_DIR}/src/")
set(lib_dir "${PROJECT_SOURCE_DIR}/lib/")

file(GLOB source_files "${source_dir}/*.cpp")

add_library(threadpool ${lib_dir}/threadpool/threadpool.cpp)
link_libraries(threadpool)

add_executable(uwuifier ${source_files})

install(TARGETS uwuifier RUNTIME DESTINATION bin)
