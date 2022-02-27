%{
#include <iostream>
#include <string>
%}

/* Flex options */
%option noyywrap

/* Flex macros */
/* Keywords */
IF              "if"
ELSE            "else"
WHILE           "while"
FOR             "for"
FUNCTION        "function"
RETURN          "return"
BREAK           "break"
CONTINUE        "continue"
AND             "and"
NOT             "not"
OR              "or"
LOCAL           "local"
TRUE            "true"
FALSE           "false"
NIL             "nil"

/* Operators */
ASSIGN          "="
PLUS            "+"
MINUS           "-"
MUL             "*"
DIV             "/"
MOD             "%"
EQUAL           "=="
NEQUAL          "!="
PLUS_PLUS       "++"
MINUS_MINUS     "--"
GT              ">"
LT              "<"
GE              ">="
LE              "<="

/* Identifiers */
ID              [a-zA-Z][a-zA-Z_0-9]*

/* Integers */
CONST_INT       ([0-9]+)
CONST_REAL      CONST_INT\.CONST_INT

/* Punctuation */
L_CURLY_BRACKET     "{"
R_CURLY_BRACKET     "}"
L_SQUARE_BRACKET    "["
R_SQUARE_BRACKET    "]"
L_PARENTHESIS       "("
R_PARENTHESIS       ")"
SEMICOLON           ";"
COMMA               ","
COLON               ":"
NAMESPACE           "::"
DOT                 "."
DOUBLE_DOT          ".."


STRING \".*(\\t)*\"
COMMENT "//".*
SPACE [\r \t\v]

%%
{IF}/[^a-zA-Z] { 
    std::cout << "Recognised IF with value: "<< yytext <<std::endl;
}  


{COMMENT} { fprintf(stderr,"Recognised COMMENT with value: %s\n",yytext); }
{SPACE} {fprintf(stderr,"Recognised SPACE with value: %s\n",yytext); }
{CONST_INT} {fprintf(stderr,"Recognised CONST_INT with value: %s\n",yytext); }
{CONST_REAL} {fprintf(stderr,"Recognised CONST_REAL with value: %s\n",yytext); }
%%

int main(int argc, char** argv){
    if(argc>1){
        if (!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return -1;
        }
    } else{
        yyin = stdin;
    }
    
    yylex();
    return 0;
}