cmake_minimum_required(VERSION 3.10)

project(BaseCompiler)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find LLVM
find_package(LLVM REQUIRED CONFIG)

# Include LLVM headers
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
link_directories(${LLVM_LIBRARY_DIRS})

# Add the executable
add_executable(basecompiler basecompiler.cc)

# Link against the required LLVM libraries
target_link_libraries(basecompiler
    LLVMCore
    LLVMExecutionEngine
    # Add other libraries as needed
)

execute_process(COMMAND llvm-config --cxxflags
                OUTPUT_VARIABLE LLVM_CXX_FLAGS)
execute_process(COMMAND llvm-config --ldflags
                OUTPUT_VARIABLE LLVM_LD_FLAGS)
execute_process(COMMAND llvm-config --libs
                OUTPUT_VARIABLE LLVM_LIBS)

target_compile_options(basecompiler PRIVATE ${LLVM_CXX_FLAGS})
target_link_libraries(basecompiler ${LLVM_LIBS})

cmake_policy(SET CMP0004 OLD)