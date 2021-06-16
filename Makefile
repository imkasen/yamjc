LEX = flex
YACC = bison
CC = g++
TARGET = compiler
NODES = ast/*.cpp

$(TARGET): lex.yy.c parser.tab.o main.cpp $(NODES)
	$(CC) -g -o $(TARGET) parser.tab.o lex.yy.c main.cpp $(NODES) -std=c++14

parser.tab.o: parser.tab.cc
	$(CC) -g -c parser.tab.cc -std=c++14

parser.tab.cc: parser.yy
	$(YACC) parser.yy

lex.yy.c: lexer.flex parser.tab.cc
	$(LEX) lexer.flex


.PHONY : all ast clean
all: $(TARGET)
ast:
	dot -T svg ast.dot -o ast.svg
clean:
	@rm -f parser.tab.* lex.yy.c* $(TARGET) stack.hh ast.*
