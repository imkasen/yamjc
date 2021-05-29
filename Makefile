LEX = flex
YACC = bison
CC = g++
OBJECT = compiler
nodes = ast/*.cpp

$(OBJECT): lex.yy.c parser.tab.o main.cpp $(nodes)
		$(CC) -g -o $(OBJECT) parser.tab.o lex.yy.c main.cpp $(nodes) -std=c++14

parser.tab.o: parser.tab.cc
		$(CC) -g -c parser.tab.cc -std=c++14

parser.tab.cc: parser.yy
		$(YACC) parser.yy

lex.yy.c: lexer.flex parser.tab.cc
		$(LEX) lexer.flex
tree: # generate ast
		dot -T svg ast.dot -o ast.svg
clean:
		@rm -f parser.tab.* lex.yy.c* $(OBJECT) stack.hh ast.*
