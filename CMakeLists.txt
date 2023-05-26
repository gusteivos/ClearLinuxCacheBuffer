
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(ClearLinuxCacheBuffer VERSION 0.2.0 DESCRIPTION "Tool to clear the cache and buffer of a linux system.")

add_definitions(-DPROGRAM_ACCEPTS_SYSTEMD) # If you do not want to support systemd, comment out this line.

file(GLOB executable_source_files
    "main.c"
    "src/*.c"
)

set(executable_header_files
    include/
)

get_directory_property(DefinitionsForTheCode DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS)

add_executable(${CMAKE_PROJECT_NAME} ${executable_source_files})

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "CLCB")

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${executable_header_files})

foreach(definition ${DefinitionsForTheCode})

    if (${definition} STREQUAL "PROGRAM_ACCEPTS_SYSTEMD")

        target_link_libraries(${CMAKE_PROJECT_NAME} systemd)

    endif()

    message(STATUS "Found Define: ${definition}")

endforeach()

message(STATUS "DefinitionsForTheCode: " ${DefinitionsForTheCode})

configure_file(${CMAKE_CURRENT_LIST_DIR}/include/program_information.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/program_information.h @ONLY)
