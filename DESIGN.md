# Interpreter Step-by-Step

### Source Code
The raw source code of my language

``` 
let item_price = 25;
let quantity = 3;
let shipping = 10;
let total = item_price * quantity + shipping;
print(total);
```

### Lexical Analysis
The lexer scans the source code character by character and groups characters into tokens representing keywords, identifiers, literals, operators, and punctuation.

```
LET IDENTIFIER("item_price") EQUAL NUMBER(25) SEMICOLON
LET IDENTIFIER("quantity") EQUAL NUMBER(3) SEMICOLON
LET IDENTIFIER("shipping") EQUAL NUMBER(10) SEMICOLON
LET IDENTIFIER("total") EQUAL IDENTIFIER("item_price") STAR IDENTIFIER("quantity") PLUS IDENTIFIER("shipping") SEMICOLON
PRINT LEFT_PAREN IDENTIFIER("total") RIGHT_PAREN SEMICOLON
EOF
```

### Parsing/AST Construction
The parser consumes tokens according to the language's grammar and constructs an Abstract Syntax Tree. Each node represents a statement or expression, and the tree preserves the program's structure and operator precedence.

```
Program
├── VariableDeclaration
│   ├── name: item_price
│   └── initializer: NumberExpression(25)
│
├── VariableDeclaration
│   ├── name: quantity
│   └── initializer: NumberExpression(3)
│
├── VariableDeclaration
│   ├── name: shipping
│   └── initializer: NumberExpression(10)
│
├── VariableDeclaration
│   ├── name: total
│   └── initializer: BinaryExpression(+)
│       ├── left: BinaryExpression(*)
│       │   ├── left: IdentifierExpression(item_price)
│       │   └── right: IdentifierExpression(quantity)
│       └── right: IdentifierExpression(shipping)
│
└── PrintStatement
    └── expression: IdentifierExpression(total)
```

### Evaluation
The interpreter traverses the AST, executing statements sequentially and recursively evaluating expressions. It maintains a symbol table that maps variable names to their runtime values.

```
VariableDeclaration("item_price")
    Evaluate NumberExpression(25)
    symbolTable["item_price"] = 25

VariableDeclaration("quantity")
    Evaluate NumberExpression(3)
    symbolTable["quantity"] = 3

VariableDeclaration("shipping")
    Evaluate NumberExpression(10)
    symbolTable["shipping"] = 10

VariableDeclaration("total")
    Evaluate BinaryExpression(+)
        Evaluate BinaryExpression(*)
            Evaluate IdentifierExpression("item_price") → 25
            Evaluate IdentifierExpression("quantity") → 3
            25 * 3 = 75

        Evaluate IdentifierExpression("shipping") → 10
        75 + 10 = 85

    symbolTable["total"] = 85

PrintStatement
    Evaluate IdentifierExpression("total") → 85
    Print 85
```

### Expected Output
```
85
```
        