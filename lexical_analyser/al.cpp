#include "scanner.h"
#include <fstream>
#include <iostream>
#include <list>

extern int alpha_yylex(void *);
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

void showlist(std::list<struct alpha_token_t *> const a, std::ostream &outfile) {
    for (struct alpha_token_t *x : a) {
        outfile << x->numline << ":\t\t"
                << "#" << x->numToken
                << "\t\t\"" << x->content << "\""
                << "\t\t\t" << x->type
                << std::endl;
    }
}

int main(int argc, char **argv) {
    std::ofstream outfile;

    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            std::cerr << "Cannot read file: " << argv[1] << std::endl;
            return -1;
        }
    } else {
        yyin = stdin;
    }

    if (argc > 2) {
        outfile.open(argv[2]);
        if (!(outfile.is_open())) {
            std::cerr << "Cannot open output file: " << argv[2] << std::endl;
            return -1;
        }
    }

    std::ostream &out = (argc > 2) ? outfile : std::cout;

    alpha_token_t *token;

    alpha_yylex(token);

    showlist(token_list, out);

    return 0;
}