# NewLang Compiler Specification

## Overview
NewLang is a compiled programming language designed to leverage the LLVM infrastructure for efficient code generation and optimization. This document outlines the specifications, syntax, semantics, and usage examples for NewLang.

## Language Features
- **Static Typing**: NewLang enforces type checking at compile time.
- **First-Class Functions**: Functions are first-class citizens, allowing for higher-order functions and closures.
- **Memory Management**: Automatic memory management with garbage collection.
- **Concurrency**: Built-in support for concurrent programming with lightweight threads.

## Syntax
### Basic Structure
A NewLang program consists of a series of declarations and expressions. The basic structure is as follows:

```newlang
function main() {
    // Your code here
}
```

### Data Types
NewLang supports the following basic data types:
- `int`: Integer type
- `float`: Floating-point type
- `string`: String type
- `bool`: Boolean type

### Variables
Variables are declared using the `let` keyword:

```newlang
let x: int = 10;
let name: string = "NewLang";
```

### Control Flow
Control flow statements include `if`, `else`, `while`, and `for`:

```newlang
if (x > 0) {
    // Do something
} else {
    // Do something else
}

while (condition) {
    // Loop body
}
```

### Functions
Functions are defined using the `function` keyword:

```newlang
function add(a: int, b: int): int {
    return a + b;
}
```

## Semantics
- **Type Checking**: The compiler performs type checking to ensure that operations are performed on compatible types.
- **Scope**: NewLang uses lexical scoping, where the scope of a variable is determined by its position in the source code.

## Usage Examples
### Hello World
A simple Hello World program in NewLang:

```newlang
function main() {
    let greeting: string = "Hello, World!";
    print(greeting);
}
```

### Factorial Function
An example of a recursive function to compute the factorial of a number:

```newlang
function factorial(n: int): int {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
```

## Conclusion
This specification provides a foundational understanding of the NewLang programming language. Further details on the implementation and additional features will be documented as the project progresses.