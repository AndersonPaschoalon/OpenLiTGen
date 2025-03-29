cmake_minimum_required(VERSION 3.10)
project(litgen-model)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../commons/include)
include_directories(${CMAKE_SOURCE_DIR}/../libs/cpptools_0.1.0.0/include)

# Source files
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE COMMONS_FILES "../commons/src/*.cpp")

# Create executable
add_executable(litgen-model ${SRC_FILES} ${COMMONS_FILES})

# Link external dependencies
target_link_libraries(litgen-model 
    ${CMAKE_SOURCE_DIR}/../libs/cpptools_0.1.0.0/bin/libcpptools.a
    tins
    pcap
    pthread
)

# Set output directory
set_target_properties(litgen-model PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

