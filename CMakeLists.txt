cmake_minimum_required(VERSION 3.10)

# Project name and language
project(tH C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Option to enable debug build
option(BUILD_DEBUG "Enable debug build" OFF)

if(BUILD_DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
    message(STATUS "Debug build enabled")
else()
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "Release build enabled")
endif()

# Collect all source files from src/
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.c)

# Create the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link against math library
target_link_libraries(${PROJECT_NAME} m)

# Output binary to /build directory inside project
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
)
