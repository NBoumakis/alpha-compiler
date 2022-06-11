#include "generators.h"
#include "include/const_pool.h"
#include "instruction.h"
#include "scope.h"
#include "scope_space.h"
#include "symbol_table.h"

#include <algorithm>
#include <cassert>
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
    for (auto &str : string_pool.get_straight())
        res += std::to_string(str.second.size()) + " " + str.second + "\n";

    return res;
}

std::string const_numbers() {
    std::string res = std::to_string(number_pool.size()) + '\n';
    for (auto &num : number_pool.get_straight())
        res += std::to_string(num.second) + "\n";

    return res;
}

std::string user_functions() {
    std::string res = std::to_string(userfunc_pool.size()) + '\n';
    for (auto func : userfunc_pool.get_straight())
        res += std::to_string(func.second->taddress) + " " +
               std::to_string(func.second->totalLocals) + " " +
               std::to_string(func.second->name.size()) + " " +
               func.second->name + "\n";

    return res;
}

std::string lib_functions() {
    std::string res = std::to_string(libfunc_pool.size()) + '\n';
    for (auto &func : libfunc_pool.get_straight())
        res += std::to_string(func.second.size()) + " " + func.second + "\n";

    return res;
}

std::string code() {
    std::string res = std::to_string(instruction_vector.size()) + '\n';
    for (auto inst : instruction_vector)
        res += inst->target_code_str() + "\n";

    return res;
}

void create_text_target(std::ofstream &out_file) {
    out_file << magic_number() << std::endl
             << std::endl;
    out_file << const_strings() << std::endl;
    out_file << const_numbers() << std::endl;
    out_file << user_functions() << std::endl;
    out_file << lib_functions() << std::endl;
    out_file << code();
}

void create_binary_target(std::ofstream &out_file) {
    unsigned long ulong = magic_number();
    out_file.write(reinterpret_cast<char *>(&ulong), sizeof(ulong));

    ulong = string_pool.size();
    out_file.write(reinterpret_cast<char *>(&ulong), sizeof(ulong));
    for (auto &str : string_pool.get_straight()) {
        ulong = str.second.size();
        out_file.write(reinterpret_cast<char *>(&ulong), sizeof(ulong));
        out_file.write(str.second.c_str(), str.second.size());
    }

    ulong = number_pool.size();
    out_file.write(reinterpret_cast<char *>(&ulong), sizeof(ulong));
    for (auto &num : number_pool.get_straight()) {
        double double_const = num.second;
        out_file.write(reinterpret_cast<char *>(&double_const), sizeof(double_const));
    }

    ulong = userfunc_pool.size();
    out_file.write(reinterpret_cast<char *>(&ulong), sizeof(ulong));
    for (auto &ufunc : userfunc_pool.get_straight()) {
        ulong = ufunc.second->taddress;
        out_file.write(reinterpret_cast<char *>(&ulong), sizeof(ulong));

        ulong = ufunc.second->totalLocals;
        out_file.write(reinterpret_cast<char *>(&ulong), sizeof(ulong));

        ulong = ufunc.second->name.size();
        out_file.write(reinterpret_cast<char *>(&ulong), sizeof(ulong));
        out_file.write(ufunc.second->name.c_str(), ufunc.second->name.size());
    }

    ulong = libfunc_pool.size();
    out_file.write(reinterpret_cast<char *>(&ulong), sizeof(ulong));
    for (auto &libfunc : libfunc_pool.get_straight()) {
        ulong = libfunc.second.size();
        out_file.write(reinterpret_cast<char *>(&ulong), sizeof(ulong));

        out_file.write(libfunc.second.c_str(), libfunc.second.size());
    }

    ulong = instruction_vector.size();
    out_file.write(reinterpret_cast<char *>(&ulong), sizeof(ulong));
    for (auto inst : instruction_vector) {
        out_file.write(reinterpret_cast<char *>(&inst->opcode), sizeof(inst->opcode));

        if (inst->arg1) {
            out_file.write(reinterpret_cast<char *>(&inst->arg1->type), sizeof(inst->arg1->type));
        } else {
            // Possible bug
            int invType = -1;
            assert(sizeof(invType) == sizeof(vmarg_t));
            out_file.write(reinterpret_cast<char *>(&invType), sizeof(vmarg_t));
        }

        if (inst->arg2) {
            out_file.write(reinterpret_cast<char *>(&inst->arg2->type), sizeof(inst->arg2->type));
        } else {
            // Possible bug
            int invType = -1;
            assert(sizeof(invType) == sizeof(vmarg_t));
            out_file.write(reinterpret_cast<char *>(&invType), sizeof(vmarg_t));
        }

        if (inst->result) {
            out_file.write(reinterpret_cast<char *>(&inst->result->type), sizeof(inst->result->type));
        } else {
            // Possible bug
            int invType = -1;
            assert(sizeof(invType) == sizeof(vmarg_t));
            out_file.write(reinterpret_cast<char *>(&invType), sizeof(vmarg_t));
        }

        if (inst->arg1) {
            out_file.write(reinterpret_cast<char *>(&inst->arg1->val), sizeof(inst->arg1->val));
        } else {
            unsigned long invValue = -1;
            out_file.write(reinterpret_cast<char *>(&invValue), sizeof(invValue));
        }

        if (inst->arg2) {
            out_file.write(reinterpret_cast<char *>(&inst->arg2->val), sizeof(inst->arg2->val));
        } else {
            unsigned long invValue = -1;
            out_file.write(reinterpret_cast<char *>(&invValue), sizeof(invValue));
        }

        if (inst->result) {
            out_file.write(reinterpret_cast<char *>(&inst->result->val), sizeof(inst->result->val));
        } else {
            unsigned long invValue = -1;
            out_file.write(reinterpret_cast<char *>(&invValue), sizeof(invValue));
        }
    }
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
            generate_target_code();

            if (cmdOptionExists(argv, argv + argc, "--binary")) {
                bin_file.open(bin_fname, std::ios::out | std::ios::binary);
                if (!(bin_file.is_open())) {
                    std::cerr << "Cannot open output for binary file: " << foutput << std::endl;
                    return -1;
                }
                create_binary_target(bin_file);
            } else {
                bin_file.open(bin_fname);
                if (!(bin_file.is_open())) {
                    std::cerr << "Cannot open output for text file: " << foutput << std::endl;
                    return -1;
                }
                create_text_target(bin_file);
            }

            bin_file.close();
        }
    } else {
        out << "Compilation failed. " << comp_err << " errors found." << std::endl;
    }
    return 0;
}