%{
#include <iostream>
#include <string>
#include <stack>
#include "y.tab.h"

int string_line_start;
%}

/* Flex options */
%option noyywrap
%option yylineno

%x str
%x multi_cmnt

/* Flex macros */
/* Keywords */
ID              [a-zA-Z][a-zA-Z_0-9]*

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


/* Integers */
CONST_INT       ([0-9]+)
CONST_REAL      ([0-9]+)\.([0-9])+

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

STRING \"
COMMENT "//".*
SPACE [\r \t\v]

%%
  char string_buf[YY_BUF_SIZE];
  char* string_buf_ptr;

"print" { return print; }
"input" { return input; }
"objectmemberkeys" { return objectmemberkeys; }
"objecttotalmembers" { return objecttotalmembers; }
"objectcopy" { return objectcopy; }
"totalarguments" { return totalarguments; }
"argument" { return argument; }
"strtonum" { return strtonum; }
"sqrt" { return sqrt; }
"cos" { return cos; }
"sin" { return sin; }


{IF} { return IF; } 

{ELSE} { return ELSE; } 

{WHILE} { return WHILE; }

{FOR} { return FOR; } 

{FUNCTION} { return FUNCTION; }

{RETURN} { return RETURN; }

{BREAK} { return BREAK; }

{CONTINUE} { return CONTINUE; }

{AND} { return AND; }

{NOT} { return NOT; }

{OR} { return OR; }

{LOCAL} { return LOCAL; }

{TRUE} { return TRUE; }

{FALSE} { return FALSE; }

{NIL} { return NIL; }





{ASSIGN} { return ASSIGN; }

{PLUS} { return PLUS; }

{MINUS} { return MINUS; }

{MUL} { return MUL; }

{DIV} { return DIV; }

{MOD} { return MOD; }

{EQUAL} { return EQUAL; }

{NEQUAL} { return NEQUAL; }

{PLUS_PLUS} { return PLUS_PLUS; }

{MINUS_MINUS} { return MINUS_MINUS; }

{GT} { return GT; }

{LT} { return LT; }

{GE} { return GE; }

{LE} { return LE; }



{CONST_INT} { yylval.intValue=atoi(yytext); return intNumber; }

{CONST_REAL} { yylval.realValue=atof(yytext); return realNumber; }



{L_CURLY_BRACKET} { return L_CURLY_BRACKET; }

{R_CURLY_BRACKET} { return R_CURLY_BRACKET; }

{L_SQUARE_BRACKET} { return L_SQUARE_BRACKET; }

{R_SQUARE_BRACKET} { return R_SQUARE_BRACKET; }

{L_PARENTHESIS} { return L_PARENTHESIS; }

{R_PARENTHESIS} { return R_PARENTHESIS; }

{SEMICOLON} { return SEMICOLON; }

{COMMA} { return COMMA; }

{COLON} { return COLON; }

{NAMESPACE} { return NAMESPACE; }

{DOT} { return DOT; }

{DOUBLE_DOT} { return DOUBLE_DOT; }

{ID} { yylval.stringValue=strdup(yytext); return ID; }



\"      {
            string_buf_ptr = string_buf;
            string_line_start = yylineno; 
            BEGIN(str);
        }
\n {}

{SPACE} {}

<str>\"        { /* saw closing quote - all done */
            BEGIN(INITIAL);
            *string_buf_ptr = '\0';
        
            yylval.stringValue=strdup(yytext); return STRING;
        }

<str>\\n  *string_buf_ptr++ = '\n';
<str>\\t  *string_buf_ptr++ = '\t';
<str>\\\"  *string_buf_ptr++ = '"';
<str>\\\\  *string_buf_ptr++ = '\\';

<str>\\(.|\n)  {
    *string_buf_ptr++ = yytext[1];
    std::cerr << "Invalid escape character " << yytext  << std::endl;
}

<str>[^\\\"]+        {
                char *yptr = yytext;

                while ( *yptr )
                    *string_buf_ptr++ = *yptr++;
            }
    
<str><<EOF>> {
    std::cerr << "EOF in string" << std::endl;
    BEGIN(INITIAL);
}

"/*"        {
                std::stack<int> cmnt_start_line;
                cmnt_start_line.push(yylineno);

                int c;
                while (c=yyinput()) {
                    if (c=='*') {
                        if ((c=yyinput())=='/') {
                            int start_line = cmnt_start_line.top();
                            yylval.stringValue=strdup(yytext);

                            if (cmnt_start_line.size()==1) {
                                std::string type = "COMMENT BLOCK_COMMENT <-enumerated";
                            } else {
                                std::string type = "NESTED COMMENT BLOCK_COMMENT <-enumerated";
                            } 

                            cmnt_start_line.pop();

                            if (cmnt_start_line.empty()){
                                break;
                            }
                        } else {
                            unput(c);
                        }
                    } else if(c=='/') {
                        if ((c=yyinput())=='*') {
                            cmnt_start_line.push(yylineno);
                        } else {
                            unput(c);
                        }
                    }
                }

                return BLOCK_COMMENT;
                if (!cmnt_start_line.empty())
                    std::cerr << "EOF in comment" << std::endl;
            }

{COMMENT}   { return COMMENT; }


{CONST_INT}[a-zA-Z_] { std::cerr << "Unknown token " << yytext << std::endl; }

{CONST_REAL}[a-zA-Z_] { std::cerr << "Unknown token " << yytext << std::endl; }

.   {
       std::cerr << "Unknown token " << yytext << std::endl;
    }

%%
