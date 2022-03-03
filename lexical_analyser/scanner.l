%{
#include <iostream>
#include <string>
%}

/* Flex options */
%option noyywrap

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

/* Identifiers */


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
    char *string_buf_ptr;
    int comment_depth;


{IF} { 
    std::cout << "Recognised IF with value: "<< yytext <<std::endl;
}  

{ID} {
    std::cout << "Identifier " << yytext << std::endl;
}

{COMMENT} { fprintf(stderr,"Recognised COMMENT with value: %s\n",yytext); }
{SPACE} {fprintf(stderr,"Recognised SPACE with value: %s\n",yytext); }
{CONST_INT} {fprintf(stderr,"Recognised CONST_INT with value: %s\n",yytext); }
{CONST_REAL} {fprintf(stderr,"Recognised CONST_REAL with value: %s\n",yytext); }

\"      string_buf_ptr = string_buf; BEGIN(str);

<str>\"        { /* saw closing quote - all done */
            BEGIN(INITIAL);
            *string_buf_ptr = '\0';
            std::cout<<"\"" <<string_buf << '"' << std:: endl;
            }

<str>\\n  *string_buf_ptr++ = '\n';
<str>\\t  *string_buf_ptr++ = '\t';
<str>\\\"  *string_buf_ptr++ = '"';

<str>\\(.|\n)  *string_buf_ptr++ = yytext[1];

<str>[^\\\"]+        {
                char *yptr = yytext;

                while ( *yptr )
                    *string_buf_ptr++ = *yptr++;
            }
    
<str><<EOF>> {
    std::cout << "EOF in string\n";
    BEGIN(INITIAL);
}

"/*"        {
                comment_depth = 1;
                BEGIN(multi_cmnt);
            }

<multi_cmnt>"/*" {
    ++comment_depth;
    std::cout<< "Comment depth: " <<comment_depth<<std::endl;
}

<multi_cmnt>[^(*|/*)]*
<multi_cmnt>"*"+[^*/]*

<multi_cmnt>"*/" {
    --comment_depth;
    if (comment_depth==0) {
        BEGIN(INITIAL);
    }
}

<multi_cmnt><<EOF>> {
    std::cout << "EOF in comment\n";
    BEGIN(INITIAL);
}
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