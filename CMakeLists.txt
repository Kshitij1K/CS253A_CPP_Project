cmake_minimum_required(VERSION 3.10)
project(LibrarySoftware)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

add_library(library src/library.cpp)

add_library(state_machine_states
            src/states/login.cpp
            src/states/professor_access.cpp
            src/states/student_access.cpp
            src/states/librarian_access.cpp)
target_link_libraries(state_machine_states library)

add_executable(main src/main.cpp)
target_link_libraries(main state_machine_states)