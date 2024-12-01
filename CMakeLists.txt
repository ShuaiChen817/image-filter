cmake_minimum_required(VERSION 3.0)
project(main)
# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set (CMAKE_CXX_FLAGS "-O2")

# Add this line for gprof profiling
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

# Find the OpenCV package
find_package(OpenCV REQUIRED)

# If OpenCV is found, output status messages and include directories
if(OpenCV_FOUND)
    message(STATUS "OpenCV library status:")
    message(STATUS "    config: ${OpenCV_DIR}")
    message(STATUS "    version: ${OpenCV_VERSION}")
    message(STATUS "    libraries: ${OpenCV_LIBS}")
    message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
    
    # Add OpenCV header file paths to the project
    include_directories(${OpenCV_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "OpenCV library not found")
endif()

file(GLOB SRC_LIST "./src/*.cpp")

include_directories(./include)

add_executable(main main.cpp ${SRC_LIST})

# Link the OpenCV library
target_link_libraries(main ${OpenCV_LIBS})