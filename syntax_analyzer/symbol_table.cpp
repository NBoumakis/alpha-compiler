#include "symbol_table.h"
#include "scope.h"
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

unsigned int funcDepth = 0;

void initSymbolTable() {
    for (auto &funcName : libFunctions) {
        Symbol *libFuncSymbol = new Function(funcName, 0, 0, 0, LIB_FUNC, 0, 0);
        symbolTableObj.insert(funcName, libFuncSymbol, 0);
    }
}