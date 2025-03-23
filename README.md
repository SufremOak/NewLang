# NewLang

NewLang is a new programming language that uses bison for the baselang. The rest of the compiler is written in NewLang itself.

## Features

- Basic syntax highlighting and language support in Visual Studio Code
- Lexer, parser, and code generator implemented using `bison` and `flex`
- Example programs included

## Getting Started

### Prerequisites

- [GNU bison](https://www.gnu.org/software/bison/)
- [Visual Studio Code](https://code.visualstudio.com/)
- [Node.js](https://nodejs.org/) and [npm](https://www.npmjs.com/) for VS Code extension development

### Building the Compiler

1. Clone the repository:
    ```sh
    git clone https://github.com/sufremoak/newlang.git
    cd newlang
    ```

2. Build the compiler:
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

### Running Example Programs

1. Navigate to the `example` directory:
    ```sh
    cd example
    ```

2. Run the example programs:
    ```sh
    ../build/newlang listfiles.new
    ../build/newlang helloworld.new
    ```

### Visual Studio Code Extension

1. Navigate to the VS Code extension directory:
    ```sh
    cd .editor/vscode
    ```

2. Install dependencies and package the extension:
    ```sh
    npm install
    vsce package
    ```

3. Install the extension in Visual Studio Code:
    ```sh
    code --install-extension newlang-0.0.1.vsix
    ```

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.

## License

This project is licensed under the MIT License.
