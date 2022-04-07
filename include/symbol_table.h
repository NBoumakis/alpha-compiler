#ifndef __SYMBOL_TABLE_H
#define __SYMBOL_TABLE_H
#include "scope.h"
#include "symbol.h"

#include <stack>
#include <unordered_set>

Scope symbolTableObj;
unsigned int scopeLevel = 0;
std::unordered_set<std::string> libFunctions = {"print",
                                                "input",
                                                "objectmemberkeys",
                                                "objecttotalmembers",
                                                "objectcopy",
                                                "totalarguments",
                                                "argument",
                                                "typeof",
                                                "strtonum",
                                                "sqrt", "cos", "sin"};

bool isLibFunction(std::string name) {
    return libFunctions.find(name) != libFunctions.end();
}

std::stack<int> def_lines_stack;
unsigned int funcDepth = 0;
#endif