#include "scanner.h"
#include <iostream>
#include <list>
#include <string>

extern int alpha_yylex(void *);
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

void showlist(std::list<struct alpha_token_t *> const a) {
    for (struct alpha_token_t *x : a) {
        std::cout << x->numline << " :"
                  << "   #" << x->numToken
                  << "   \"" << x->content << "\""
                  << "   " << x->type
                  << std::endl;
    }
}

int main(int argc, char **argv) {
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return -1;
        }
    } else {
        yyin = stdin;
    }

    alpha_token_t *token;

    alpha_yylex(token);

    showlist(token_list);

    return 0;
}