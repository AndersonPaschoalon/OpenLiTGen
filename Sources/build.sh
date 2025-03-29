#!/bin/bash

# Function to clean the entire project
clean() {
    echo "Cleaning project..."

    # Remove generated files in litgen-model
    rm -rf litgen-model/{obj,build,bin}

    # Remove generated files in litgen-tg
    rm -rf litgen-tg/{obj,build,bin}

    # Remove binaries in the root ./bin directory
    rm -rf ./bin/*

    echo "Clean completed."
}

# Function to build a sub-project (litgen-model or litgen-tg)
build_subproject() {
    local project_dir=$1

    echo "Building project: $project_dir..."

    # Go to the subproject directory
    cd $project_dir

    # Create a build directory if it doesn't exist
    mkdir -p build
    cd build

    # Run cmake to configure the project
    cmake ..

    # Build the project using make
    make

    # Go back to the root directory
    cd ../../

    echo "Build completed for: $project_dir."
}

# Function to copy generated binaries to the root ./bin directory
copy_binaries() {
    echo "Copying binaries to root ./bin directory..."

    # Copy the generated binaries from litgen-model and litgen-tg to the root bin directory
    cp litgen-model/bin/* ./bin/
    cp litgen-tg/bin/* ./bin/

    echo "Binaries copied."
}

# Main script logic: process the command-line argument
if [ "$1" == "--clean" ]; then
    clean
elif [ "$1" == "--build" ]; then
    # Build both sub-projects
    build_subproject litgen-model
    build_subproject litgen-tg

    # Copy the generated binaries to the root ./bin
    copy_binaries

    echo "Build process completed."
else
    echo "Usage: $0 --clean | --build"
    exit 1
fi

