cmake_minimum_required(VERSION 3.25)

project(uwuifier VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

set(source_dir "${PROJECT_SOURCE_DIR}/src/")
set(lib_dir "${PROJECT_SOURCE_DIR}/lib/")

set(UWUIFIED 1)

file(GLOB source_files "${source_dir}/*.cpp")
file(GLOB header_files "${source_dir}/*.h")

add_executable(uwuifier main.cpp ${source_files} ${header_files})

add_subdirectory("./DArgumentParser")

target_include_directories(uwuifier PRIVATE "./DArgumentParser" ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(uwuifier DArgumentParser)

configure_file(cmake_config.h.in cmake_config.h)

install(TARGETS uwuifier RUNTIME DESTINATION bin)
