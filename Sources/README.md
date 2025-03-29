# Building and Cleaning the Project

This directory contains the source code for the **OpenLitGen** project, including both the `litgen-model` and `litgen-tg` binaries.

## Requirements
Before building the project, ensure you have the following installed:
- **CMake** (version 3.10 or higher)
- **g++** (C++ compiler)
- **Tins** library
- **libpcap** library
- **pthread** library
- **cpptools** (internal utility library)

## Building the Project

To build the project, follow these steps:

1. Navigate to the `Sources/` directory:
```bash
OpenLitGen/Sources/
```

2. Run the following command to build the project:
```bash
./build.sh --build
```

This will:
- Build both litgen-model and litgen-tg sub-projects.
- Place the generated executables in the ./bin/ directory at the root of the project.


## Cleaning the Project

To clean the project and remove all generated files, including object files, binaries, and build files, run the following command:
```bash
./build.sh --clean
```

This will:
- Remove all files in litgen-model/{obj,build,bin}, litgen-tg/{obj,build,bin}, and ./bin/ directories.


