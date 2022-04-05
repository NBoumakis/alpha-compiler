#include "../include/scope.h"
#include "../include/symbol.h"

#include <unordered_set>

class Symbol_Table {
public:
    static Scope symbolTable;
    static int scopeLevel;
    static std::unordered_set<std::string> libFunctions;

    static bool isLibFunction(std::string name) {
        return libFunctions.find(name) != libFunctions.end();
    }
};