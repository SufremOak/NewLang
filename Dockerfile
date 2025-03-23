# Use an official LLVM image as a base
FROM llvm/llvm:latest

# Set the working directory
WORKDIR /app

# Install necessary packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    clang \
    libllvm-<version>-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy the source code into the container
COPY . .

# Build the project
RUN mkdir build && cd build && cmake .. && make

# Command to run the compiler
CMD ["./build/basecompiler"]
