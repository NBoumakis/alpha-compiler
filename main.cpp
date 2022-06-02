#include "generators.h"
#include "include/const_pool.h"
#include "instruction.h"
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

unsigned long magic_number() {
    return 340200501;
}

std::string const_strings() {
    std::string res = std::to_string(string_pool.size()) + '\n';
    for (auto &str : string_pool)
        res += std::to_string(str.size()) + " " + str + "\n";

    return res;
}

std::string const_numbers() {
    std::string res = std::to_string(number_pool.size()) + '\n';
    for (auto &num : number_pool)
        res += std::to_string(num) + "\n";

    return res;
}

std::string user_functions() {
    std::string res = std::to_string(userfunc_pool.size()) + '\n';
    for (auto func : userfunc_pool)
        res += std::to_string(func->iaddress) + " " + std::to_string(func->totalLocals) + " " + func->name + "\n";

    return res;
}

std::string lib_functions() {
    std::string res = std::to_string(libfunc_pool.size()) + '\n';
    for (auto &func : libfunc_pool)
        res += std::to_string(func.size()) + " " + func + "\n";

    return res;
}

std::string code() {
    std::string res = std::to_string(instruction_vector.size()) + '\n';
    for (auto inst : instruction_vector)
        res += inst->target_code_str() + "\n";

    return res;
}

void create_target(std::ofstream &out_file) {
    generate_target_code();

    out_file << magic_number() << std::endl
             << std::endl;
    out_file << const_strings() << std::endl;
    out_file << const_numbers() << std::endl;
    out_file << user_functions() << std::endl;
    out_file << lib_functions() << std::endl;
    out_file << code();
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

        char *bin_fname = getCmdOption(argv, argv + argc, "--target");
        std::ofstream bin_file;

        if (bin_fname) {
            bin_file.open(bin_fname);
            if (!(bin_file.is_open())) {
                std::cerr << "Cannot open output for binary file: " << foutput << std::endl;
                return -1;
            }

            create_target(bin_file);
        }
    } else {
        out << "Compilation failed. " << comp_err << " errors found." << std::endl;
    }
    return 0;
}