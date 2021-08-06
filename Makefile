LEX      := flex
YACC     := bison
CC       := g++
TARGET   := compiler
NODES    := source/ast/*.cpp
ST_IMPLS := source/st/*.cpp
STD      := -std=c++17

$(TARGET): lex.yy.c parser.tab.o source/main.cpp $(NODES) $(ST_IMPLS)
	$(CC) -g -o $(TARGET) parser.tab.o lex.yy.c source/main.cpp $(NODES) $(ST_IMPLS) $(STD)

parser.tab.o: parser.tab.cc
	$(CC) -g -c parser.tab.cc $(STD)

parser.tab.cc: source/parser.yy
	$(YACC) source/parser.yy

lex.yy.c: source/lexer.ll
	$(LEX) source/lexer.ll


.PHONY : all graph ast st clean
all: $(TARGET)
graph: ast st
ast:
	dot -T svg ast.dot -o ast.svg
st:
	dot -T svg st.dot -o st.svg
clean:
	@rm -f parser.tab.* lex.yy.c* $(TARGET) ast.* st.*
