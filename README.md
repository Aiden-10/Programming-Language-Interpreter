# Programming Language Interpreter

A simple programming language interpreter written in C++.

## Features
- Lexical analysis and tokenization
- Recursive-descent parsing
- Abstract syntax tree (AST)
- Variable declarations and symbol table
- Arithmetic expression evaluation
- Print statements
- Error handling and unit tests

## Example

```js
let x = 10;
let y = 5;
let z = x + y;
print(z);
```

Output:
```
15
```

## Building

Compile using MSVC:

```cmd
cl /std:c++20 /EHsc main.cpp
```

## Tests

```cmd
cd __tests__
cl /std:c++20 /EHsc test.cpp /Fe:tests.exe
tests.exe
```