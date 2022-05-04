# @Author: Katerina Lionta
# @Author: Konstantina Papafragkaki
# @Author: Nikos Boumakis

CCpp = g++
Lexer = flex
ParserGen = bison

INCLUDE_DIR = ./include

CppOptions 	= -I$(INCLUDE_DIR) -std=c++14 -g -Wall #-Wno-uninitialized
ParserGenOptions = --yacc --defines 



all: prepare scanner parser analyzer

prepare:
	-clear
	@echo -e "\e[0;33mStarting build\e[0m"
	@echo -e "\e[0;33mPreparing filesystem\e[0m"
	-rm -rf build
	-mkdir build
	@echo

scanner:
	@echo -e "\e[0;33mMaking lexical analyser\e[0m"
	$(Lexer) --outfile=./build/scanner.cpp ./lexical_analyser/scanner.l
	@echo

parser:
	@echo -e "\e[0;33mMaking syntax analyser\e[0m"
	$(ParserGen) $(ParserGenOptions) --output=./build/parser.cpp ./syntax_analyzer/parser.y
	@echo


analyzer:
	@echo -e "\e[0;33mMaking parser\e[0m"
	$(CCpp) $(CppOptions)  build/*.cpp lib/*.cpp syntax_analyzer/*.cpp intermediate_code/*.cpp -o ./build/parser

clean:
	-rm -rf build
