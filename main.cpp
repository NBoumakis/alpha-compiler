#include "scope.h"
#include "scope_space.h"
#include "symbol_table.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

extern FILE *yyin;
extern std::unordered_set<std::string> libFunctions;

extern FILE *yyin;

extern Scope symbolTableObj;

extern std::string quad_to_string();
extern void yyparse();

unsigned comp_err = 0;

char *getCmdOption(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return nullptr;
}

bool cmdOptionExists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

int main(int argc, char *argv[]) {
    std::ofstream outfile;

    char *finput = getCmdOption(argv, argv + argc, "--in");
    char *foutput = getCmdOption(argv, argv + argc, "--out");

    if (finput) {
        if (!(yyin = fopen(finput, "r"))) {
            std::cerr << "Cannot read file: " << finput << std::endl;
            return -1;
        }
    } else {
        yyin = stdin;
    }

    if (foutput) {
        outfile.open(foutput);
        if (!(outfile.is_open())) {
            std::cerr << "Cannot open output file: " << foutput << std::endl;
            return -1;
        }
    }

    std::ostream &out = (foutput) ? outfile : std::cout;

    initSymbolTable();
    init_quad_vector();

    yyparse();

    if (cmdOptionExists(argv, argv + argc, "--symbol"))
        symbolTableObj.get_symbols_scope_order();

    if (!comp_err) {
        if (cmdOptionExists(argv, argv + argc, "--quad"))
            out << quad_to_string();
    } else {
        out << "Compilation failed. " << comp_err << " errors found." << std::endl;
    }
    return 0;
}