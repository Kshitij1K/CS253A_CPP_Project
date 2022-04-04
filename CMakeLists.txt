cmake_minimum_required(VERSION 3.10)
project(LibrarySoftware)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

add_library(state_machine src/state_machine.cpp)

add_executable(main src/main.cpp)
target_link_libraries(main state_machine)