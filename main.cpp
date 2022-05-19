#include "scope.h"
#include "scope_space.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

extern FILE *yyin;
extern std::unordered_set<std::string> libFunctions;

extern int yylineno;
extern char *yytext;
extern FILE *yyin;

extern Scope symbolTableObj;
extern unsigned int scopeLevel;

extern std::string quad_to_string();
extern void yyparse();

int main(int argc, char *argv[]) {
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

    for (auto &funcName : libFunctions) {
        // TODO
        Symbol *libFuncSymbol = new Function(funcName, 0, 0, 0, LIB_FUNC, 0, 0);
        symbolTableObj.insert(funcName, libFuncSymbol, 0);
    }

    quad p;

    p.arg1 = nullptr;
    p.arg2 = nullptr;
    p.result = nullptr;
    p.line = -1;
    p.label = -1;

    quad_vector.push_back(p);

    yyparse();

    symbolTableObj.get_symbols_scope_order();
    out << quad_to_string() << std::endl;
    return 0;
}