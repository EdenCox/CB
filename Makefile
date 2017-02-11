CCC = g++



parser.tab.c parser.tab.h: parser.y
	bison -d parser.y --verbose

lex.yy.c: parser.l parser.tab.h
	flex parser.l

parser: lex.yy.c parser.cpp parser.h SymbolTable.cpp SymbolTable.h parser.tab.c parser.tab.h
	${CCC} parser.tab.c lex.yy.c parser.cpp SymbolTable.cpp -lfl -o parser -std=c++11

