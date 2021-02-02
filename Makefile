LEX = flex
CC = g++
OBJECT = compiler

$(OBJECT): lex.yy.c main.cpp
	$(CC) lex.yy.c main.cpp -o $(OBJECT) 

lex.yy.c: lexer.flex
	$(LEX) lexer.flex

clean:
	@rm -f lex.yy.c $(OBJECT)