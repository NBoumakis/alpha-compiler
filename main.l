%{
#include <iostream>
#include <string>

enum token_value {
    ALERT,BACKSPACE,ESCAPE,FORMFEED,NEWLINE,
    RETURN,TAB,V_TAB,BACKSLASH,APOSTROPHE,
    DOUBLE_APO,Q_MARK
};

std::string enum_to_string_flex(token_value type) {
   switch(type) {
      case ALERT:
         return "\\a";
      case BACKSPACE:
         return "\\b";
      case ESCAPE:
         return "\\e";
      case FORMFEED:
         return "\\f";
      case NEWLINE:
         return "\\n";
      case RETURN:
         return "\\r";
      case TAB:
         return "\\t";
      case V_TAB:
         return "\\v";
      case BACKSLASH:
         return "\\\\";
      case APOSTROPHE:
         return "\\'";
      case DOUBLE_APO:
         return "\\""";
      case Q_MARK:
         return "\\?";
   }
}

std::string enum_to_result(token_value type) {
   switch(type) {
      case ALERT:
         return "\a";
      case BACKSPACE:
         return "\b";
      case ESCAPE:
         return "\e";
      case FORMFEED:
         return "\f";
      case NEWLINE:
         return "\n";
      case RETURN:
         return "\r";
      case TAB:
         return "\t";
      case V_TAB:
         return "\v";
      case BACKSLASH:
         return "\\";
      case APOSTROPHE:
         return "\'";
      case DOUBLE_APO:
         return "\"";
      case Q_MARK:
         return "\?";
   }
}

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


STRING \".*(\\)*\"
COMMENT "//".*
SPACE [\r \t\v]

%%
{IF}/[^a-zA-Z] { 
    std::cout << "Recognised IF with value: "<< yytext <<std::endl;
} 

{STRING} {      std::string a(yytext);
                size_t position;
                for ( int token= token_value::ALERT; token != token_value::Q_MARK; token++){

                    while ((position=a.find(enum_to_string_flex(static_cast<token_value>(token)))) != std::string::npos) {
                        a.replace(position, 2, enum_to_result(static_cast<token_value>(token)));
                    }

                }
                
                std::cout << "Recognised STRING with value: " << a << std::endl; } 

{COMMENT} { std::cout << "Recognised COMMENT with value: " << yytext << std::endl; }
{SPACE} { std::cout << "Recognised SPACE with value: " << yytext << std::endl; }
{CONST_INT} { std::cout << "Recognised CONST_INT with value: " << yytext << std::endl; }
{CONST_REAL} { std::cout << "Recognised CONST_REAL with value: " << yytext << std::endl; }
%%

int main(int argc, char** argv){
    if (argc > 1){
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