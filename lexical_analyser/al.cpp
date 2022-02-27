#include "myscanner.h"
#include <iostream>
#include <string>

extern int yylex();
extern int yylineno;
extern char *yytext;

std::string names[] = {NULL, "db_type", "db_name", "db_table_prefix", "db_port"};

int main() {
    int ntoken, vtoken;
    ntoken = yylex();
    while (ntoken) {
        std::cout << ntoken << yytext; /*if(yylex() != COLON){ printf("syntax error ,expected colon but found %s\n ",yytext); return -1; }*/
        ntoken = yylex();
    }
    return 0;
}