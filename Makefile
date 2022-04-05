# @Author: Katerina Lionta
# @Author: Konstantina Papafragkaki
# @Author: Nikos Boumakis

CCpp = g++
Lexer = flex
ParserGen = bison

INCLUDE_DIR = ./include

CppOptions 	= -I$(INCLUDE_DIR) -std=c++11 -g
ParserGenOptions = --yacc --defines 



all: prepare scanner parser analyzer

prepare:
	-clear
	-rm -rf build
	-mkdir build

scanner:
	$(Lexer) --outfile=./build/scanner.cpp ./lexical_analyser/scanner.l

parser:
	$(ParserGen) $(ParserGenOptions) --output=./build/parser.cpp ./syntax_analyzer/parser.y


analyzer:
	$(CCpp) $(CppOptions) ./build/scanner.cpp ./build/parser.cpp -o ./build/parser

clean:
	-rm -rf build
