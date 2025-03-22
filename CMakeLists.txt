cmake_minimum_required(VERSION 3.10)

project(NewLang)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the LLVM package
# find_package(LLVM REQUIRED CONFIG)

# Include the LLVM headers
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Add the executable
add_executable(basecompiler basecompiler.cc)

# Link the LLVM libraries
llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(basecompiler ${llvm_libs})