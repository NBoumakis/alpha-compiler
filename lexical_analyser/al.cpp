#include "scanner.h"
#include <iostream>
#include <list>
#include <string>

extern int yylex();
extern int yylineno;
extern char *yytext;

void showlist(std::list<struct alpha_token_t *> const a) {
    for (struct alpha_token_t *x : a) {
        std::cout << x->numline << " :"
                  << "   #" << x->numToken
                  << "   \"" << x->content << "\""
                  << "   " << x->type
                  << std::endl;
    }
}

int main() {
    int ntoken, vtoken;
    ntoken = yylex();
    while (ntoken) {
        std::cout << ntoken << yytext; /*if(yylex() != COLON){ printf("syntax error ,expected colon but found %s\n ",yytext); return -1; }*/
        ntoken = yylex();
    }
    return 0;
}