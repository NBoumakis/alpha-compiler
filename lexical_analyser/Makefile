# @Author: Katerina Lionta
# @Author: Konstantina Papafragkaki
# @Author: Nikos Boumakis

CCpp = g++
Lexer = flex

all: scanner analyzer

scanner: scanner.l
	$(Lexer) scanner.l

analyzer: lex.yy.c al.cpp scanner.cpp
	$(CCpp) lex.yy.c al.cpp scanner.cpp -o al

clean:
	-rm -f lex.yy.c al