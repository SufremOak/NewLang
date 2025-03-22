cmake_minimum_required(VERSION 3.10)

project(NewLang)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the LLVM package
find_package(LLVM REQUIRED CONFIG)

# Include the LLVM directories
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

# Add the executable
add_executable(basecompiler basecompiler.cc)

# Link the LLVM libraries
target_link_libraries(basecompiler ${LLVM_LIBS})