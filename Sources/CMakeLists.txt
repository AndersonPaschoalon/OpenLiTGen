cmake_minimum_required(VERSION 3.10)
project(OpenLitGen)

# Set the global binary directory to be './bin'
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Ensure that sub-projects use the global CMake settings (e.g., C++ standard, include directories)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the sub-projects
add_subdirectory(litgen-model)
add_subdirectory(litgen-tg)

# Optionally, specify a global include directory that all sub-projects should use
include_directories(${CMAKE_SOURCE_DIR}/commons/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/cpptools_0.1.0.0/include)

# Optionally, set any global libraries or link settings (if applicable)
# This can be customized as needed, based on external libraries used across all sub-projects

