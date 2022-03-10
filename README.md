# Yet Another Mini-Java Compiler

A compiler practice implemented in C++ with poor structure and bad design.

## What is Mini-Java?

> MiniJava is a subset of Java. The meaning of a MiniJava program is given by its meaning as a Java program.  
>
> Overloading is not allowed in MiniJava. The MiniJava statement `System.out.println( ... );` can only print integers. The MiniJava expression `e.length` only applies to expressions of type `int []`.

There are four types only, which are `int`, `boolean`, `int[]`, and user-defined class. There is no `for` loop or `do {} while ()` in MiniJava, `if` statement must be followed by `else` statement, etc... Please refer to the _Grammar_ section below for the detailed grammar.

## Grammar

* [BNF for MiniJava](https://www.cambridge.org/us/features/052182060X/grammar.html)
* [BNF for MiniJava](https://web.cs.ucla.edu/classes/spring11/cs132/cs132/mj/minijava.html)

## System Requirements

* Ubuntu 20.04 LTS x86_64
* g++ 9.3.0
* [CMake](https://cmake.org/) 3.16.3
* [Graphviz](https://graphviz.org/) 2.43.0
* [flex](https://github.com/westes/flex) 2.6.4
* [Bison](https://www.gnu.org/software/bison/bison.html) 3.5.1

## Compiler Phases

<div align="center">
  <img src="resource/phases-light.png#gh-light-mode-only" width="800" height="auto" alt="Compiler Phases">
  <img src="resource/phases-dark.png#gh-dark-mode-only" width="800" height="auto" alt="Compiler Phases">
</div>

## File structure

* `include/` : header files
* `resource/`
  * `examples/` : files used for testing lexical & syntax analysis
  * `tests/` : files used for back-end stage
  * `valid/` : files used for testing semantic analysis
* `src/` : source files
  * `ast/` : abstract syntax tree
  * `cfg/` : intermediate representation
  * `smi/` : stack machine interpreter
  * `st/` : symbol table
  * `main.cpp`
  * `lexer.ll` : flex file
  * `parser.yy` : Bison file

## Usage

``` shell
# Build:
$ mkdir build/ && cd build/
$ cmake ..
$ make  # or: cmake --build .
# generated file:
# compiler

# Run:
$ ./compiler <file_path>  # e.g. "../resource/tests/Minimal.java"
# output results,
# generated files:
# ast.dot, st.dot, cfg.dot
# rbc.class

# Visualize:
$ sh graph.sh
# generated files:
# ast.svg, st.svg, cfg.svg

# Clean:
$ make clean  # or: cd .. && rm -rf build/
```

## LICENSE

GNU GPL v3
