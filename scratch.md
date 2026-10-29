# Interpreter Step-by-Step

### Source Code
The raw source code of my language

``` 
let interest_rate = 10;
let price = 5;
let z = interest_rate + price;
print(z);
```

### Lexical Analysis
The lexer scans the source code character by character and groups characters into tokens representing keywords, identifiers, literals, operators, and punctuation.

```
LET IDENTIFIER("interest_rate") EQUAL NUMBER(10) SEMICOLON
LET IDENTIFIER("price") EQUAL NUMBER(5) SEMICOLON
LET IDENTIFIER("z") EQUAL IDENTIFIER("interest_rate") PLUS IDENTIFIER("price") SEMICOLON
PRINT LEFT_PAREN IDENTIFIER("z") RIGHT_PAREN SEMICOLON
EOF
```

### Parsing/AST Construction
The parser consumes tokens according to the language's grammar and constructs an Abstract Syntax Tree. Each node represents a statement or expression, and the tree preserves the program's structure and operator precedence.

```
VariableDeclaration
    name: interest_rate
    initializer:
        NumberExpression
            value: 10

VariableDeclaration
    name: price
    initializer:
        NumberExpression
            value: 5

VariableDeclaration
    name: z
    initializer:
        BinaryExpression
            op: '+'
            left:
                IdentifierExpression
                    name: interest_rate
            right:
                IdentifierExpression
                    name: price

PrintStatement
    expression:
        IdentifierExpression
            name: z
```

### Evaluation
The interpreter traverses the AST, executing statements sequentially and recursively evaluating expressions. It maintains a symbol table that maps variable names to their runtime values.

```
VariableDeclaration("interest_rate")
    Evaluate NumberExpression(10)
    symbolTable["interest_rate"] = 10

VariableDeclaration("price")
    Evaluate NumberExpression(5)
    symbolTable["price"] = 5

VariableDeclaration("z")
    Evaluate BinaryExpression(+)
        Evaluate IdentifierExpression("interest_rate") → 10
        Evaluate IdentifierExpression("price") → 5
        10 + 5 = 15
    symbolTable["z"] = 15

PrintStatement
    Evaluate IdentifierExpression("z") → 15
    Print 15
```
        