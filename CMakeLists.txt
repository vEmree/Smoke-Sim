cmake_minimum_required(VERSION 3.10)

# Project name
project(smokeSim C)

# Set C standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Recursively gather all .c files in src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.c
)


# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Find and link raylib
find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} raylib)