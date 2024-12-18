# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(ImageFiltering)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include directories for headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(image_filtering
    src/main.cpp
    src/UserMenu.cpp
    src/filters.cpp
)

# Link OpenCV libraries
target_link_libraries(image_filtering ${OpenCV_LIBS})
