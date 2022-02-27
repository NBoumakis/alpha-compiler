%{
#include <iostream>
#include <string>
%}

/* Flex options */
%option noyywrap

/* Flex macros */
STRING \".*(\\t)*\"
COMMENT "//".*
SPACE [\r \t\v]
CONST_INT (0[xX][0-9A-Fa-f]+)|([0-9]+)
CONST_REAL ([0-9]*)\.[0-9](e|E)?[0-9]*

%%
{STRING} { fprintf(stderr,"Recognised STRING with value: %s\n", yytext); }  
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