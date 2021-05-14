LEX = flex
YACC = bison
CC = g++
OBJECT = compiler
nodes = nodes/*.cpp

$(OBJECT): lex.yy.c parser.tab.o main.cpp $(nodes)
		$(CC) -g -o $(OBJECT) parser.tab.o lex.yy.c main.cpp $(nodes) -std=c++14

parser.tab.o: parser.tab.cc
		$(CC) -g -c parser.tab.cc -std=c++14

parser.tab.cc: parser.yy
		$(YACC) parser.yy

lex.yy.c: lexer.flex parser.tab.cc
		$(LEX) lexer.flex
tree: 
		dot -T pdf tree.dot -o tree.pdf
clean:
		@rm -f parser.tab.* lex.yy.c* $(OBJECT) stack.hh tree.dot tree.pdf
		# @rm -R compiler.dSYM
