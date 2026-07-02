# Lexical Analyzer & Operator Precedence Parser

A **COMP 451 Compiler Construction** class project implemented in C. This project demonstrates two important phases of a compiler front-end: **lexical analysis** and **operator precedence parsing** for simple arithmetic expressions.

The system accepts arithmetic expressions containing lowercase single-letter identifiers and arithmetic operators. It identifies valid tokens, checks the expression using a precedence-based parsing approach, and evaluates the final result using stack-based logic.

---

## Project Overview

This project contains two main programs:

1. **Lexical Analyzer**
   - Scans the input expression character by character.
   - Identifies identifiers, operators, sentinel symbols, and invalid tokens.
   - Helps validate the structure of arithmetic expressions.

2. **Operator Precedence Parser**
   - Parses arithmetic expressions using operator precedence rules.
   - Uses stack-based parsing to evaluate expressions.
   - Displays parsing steps and final output.

---

## Features

- Lexical analysis of arithmetic expressions
- Token classification for identifiers and operators
- Operator precedence parsing
- Stack-based expression evaluation
- Support for arithmetic operators:
  - Addition `+`
  - Subtraction `-`
  - Multiplication `*`
  - Division `/`
- Sentinel-based input handling using `$`
- Error handling for invalid tokens
- Division-by-zero detection
- Step-by-step parsing output

---

## Technologies Used

- **Programming Language:** C
- **Compiler:** GCC
- **Course Concepts Used:**
  - Compiler Construction
  - Lexical Analysis
  - Parsing
  - Operator Precedence
  - Stack Data Structure
  - Expression Evaluation

---

## Project Structure

```text
COMP451_261034399_classProject/
│
├── lexer.c
├── parser.c
└── Report.pdf
```

---

## How to Compile

Use the following commands to compile the programs:

```bash
gcc lexer.c -o lexer
gcc parser.c -o parser
```

For Windows:

```bash
gcc lexer.c -o lexer.exe
gcc parser.c -o parser.exe
```

---

## How to Run

### Run the Lexical Analyzer

```bash
./lexer 'a+b*c$'
```

For Windows:

```bash
lexer.exe "a+b*c$"
```

### Run the Parser

```bash
./parser 'a+b*c$'
```

For Windows:

```bash
parser.exe "a+b*c$"
```

---

## Example Expression

```text
a+b*c$
```

The `$` symbol is used as the end marker of the expression.

---

## Example Input

```text
Value of a: 2
Value of b: 5
Value of c: 10
```

---

## Example Output

```text
The output of the given expression is: 52
```

---

## Important Note

The expression must end with the `$` symbol.

Example:

```text
a+b*c$
```

Use quotes around the expression when running the program, because some terminals treat `$` as a special character.

Correct:

```bash
./parser 'a+b*c$'
```

---

## Limitations

- Only lowercase single-letter identifiers are supported.
- Multi-character variable names are not supported.
- Numeric constants inside the expression are not supported.
- Parentheses are not supported.
- Unary minus is not supported.
- The lexer supports a limited number of operands.

---

## Course Information

- **Course:** COMP 451 — Compiler Construction
- **Project Type:** Class Project
- **Topic:** Lexical Analyzer and Operator Precedence Parser
- **Semester:** Spring 2026

---

## Contributors

This project was developed as a group class project for COMP 451 Compiler Construction.

---

## Purpose

The main purpose of this project is to understand how a compiler processes arithmetic expressions in its early stages. It shows how input is broken into tokens through lexical analysis and then parsed according to operator precedence rules.

---

## License

This project is intended for academic and learning purposes.
