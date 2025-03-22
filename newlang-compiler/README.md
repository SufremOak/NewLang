# NewLang Compiler

NewLang is a compiled programming language designed to leverage the LLVM infrastructure for efficient code generation. This project aims to provide a robust compiler that is extensible and easy to use.

## Project Structure

- **src/**: Contains the source code for the NewLang compiler.
  - **main.newlang**: Entry point for the compiler.
  - **lexer/**: Implements the lexer for NewLang.
  - **parser/**: Implements the parser for NewLang.
  - **codegen/**: Handles code generation to LLVM IR.
  - **utils/**: Contains utility functions and helpers.

- **llvm/**: Contains integration code for LLVM.
  - **llvm_integration.cpp**: C++ code for LLVM setup and compilation.

- **build/**: Contains build scripts.
  - **build_script.sh**: Automates the build process.

- **docs/**: Documentation for NewLang.
  - **specification.md**: Language specification and usage examples.

- **tests/**: Contains test cases for various components of the compiler.
  - **lexer_tests.newlang**: Tests for the lexer.
  - **parser_tests.newlang**: Tests for the parser.
  - **codegen_tests.newlang**: Tests for code generation.

- **.gitignore**: Specifies files and directories to ignore in version control.

## Setup Instructions

1. Clone the repository:
   ```
   git clone <repository-url>
   cd newlang-compiler
   ```

2. Build the project:
   ```
   ./build/build_script.sh
   ```

3. Run the compiler:
   ```
   ./path/to/compiled/newlang <source-file.newlang>
   ```

## Usage

To compile a NewLang source file, use the command line interface provided by the compiled binary. The compiler will process the source code and generate the corresponding LLVM IR.

## Contribution Guidelines

Contributions are welcome! Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Make your changes and commit them.
4. Push your branch and create a pull request.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.