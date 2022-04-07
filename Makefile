# @Author: Katerina Lionta
# @Author: Konstantina Papafragkaki
# @Author: Nikos Boumakis

CCpp = g++
Lexer = flex
ParserGen = bison

INCLUDE_DIR = ./include

CppOptions 	= -I$(INCLUDE_DIR) -std=c++14 -g
ParserGenOptions = --yacc --defines 



all: prepare scanner parser analyzer

prepare:
	-clear
	-rm -rf build
	-mkdir build
	-echo

scanner:
	$(Lexer) --outfile=./build/scanner.cpp ./lexical_analyser/scanner.l
	-echo

parser:
	$(ParserGen) $(ParserGenOptions) --output=./build/parser.cpp ./syntax_analyzer/parser.y
	-echo


analyzer:
	$(CCpp) $(CppOptions) build/scanner.cpp build/parser.cpp syntax_analyzer/rules.cpp lib/scope.cpp syntax_analyzer/symbol.cpp -o ./build/parser

clean:
	-rm -rf build
