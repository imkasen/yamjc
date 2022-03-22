# Yet Another Mini-Java Compiler

A compiler practice implemented in C++ with poor structure and bad design.

## What is Mini-Java?

> MiniJava is a subset of Java. The meaning of a MiniJava program is given by its meaning as a Java program.  
>
> Overloading is not allowed in MiniJava. The MiniJava statement `System.out.println( ... );` can only print integers. The MiniJava expression `e.length` only applies to expressions of type `int []`.

There are four types only, which are `int`, `boolean`, `int[]`, and user-defined class. There is no `for` loop or `do while` statement in MiniJava, `if` statement must be followed by `else` statement, etc... Please refer to the *BNF* section below for more specific grammar.

## Backus Normal Form

* [BNF for MiniJava](https://www.cambridge.org/us/features/052182060X/grammar.html)
* [BNF for MiniJava](https://web.cs.ucla.edu/classes/spring11/cs132/cs132/mj/minijava.html)

## Dependencies

* Ubuntu 20.04 LTS x86_64
* g++ 9.3.0
* [CMake](https://cmake.org/) 3.16.3
* [Graphviz](https://graphviz.org/) 2.43.0
* [flex](https://github.com/westes/flex) 2.6.4
* [Bison](https://www.gnu.org/software/bison/bison.html) 3.5.1

## Compile Phases

<div align="center">
  <img src="resource/phases-light.png#gh-light-mode-only" width="800" height="auto" alt="Compiler Phases">
  <img src="resource/phases-dark.png#gh-dark-mode-only" width="800" height="auto" alt="Compiler Phases">
</div>

## File Structures

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

## Run Locally

``` Bash
# Build:
$ mkdir build/ && cd build/
$ cmake ..
$ make  # or: cmake --build .
# generated file:
# compiler

# Run:
$ ./compiler [-i] <file_path>  # e.g. "../resource/tests/Minimal.java"
# generated files:
# ast.dot, st.dot, cfg.dot
# if using '-i', 
# generate 'rbc.class' and output results

# Visualize:
$ bash graph.sh
# generated files:
# ast.svg, st.svg, cfg.svg

# Clean:
$ make clean  # or: cd .. && rm -rf build/
```

### Docker

``` Bash
# Build:
$ docker build -t mjc .
$ docker image prune

# Run:
$ docker run -it --rm --mount type=bind,source=<your_path>/build,target=/home/build mjc
$ cd build/
$ ../compiler [-i] ../tests/<file_name>.java

# Visualize
$ bash ../graph.sh

# Quit:
$ exit
# generated files still can be found in "build" folder

# Clean:
$ docker image rm mjc
```

## Known Issues

TLDR: The interpreter phase *(use `-i` to enable)* currently only supports processing `int` and `boolean` type variables declared in *method* scopes.

All phases except the interpreter work well for all provided Java cases. The interpreter only works well for Java cases in the `resource/tests` folder but crashes when executing cases in the `resource/examples` folder because it does not yet support variable declarations in class scopes and support for arrays.

## License

[GNU GPL v3](https://choosealicense.com/licenses/gpl-3.0/)
