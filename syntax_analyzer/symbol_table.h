#include "scope.h"
#include "symbol.h"

#include <unordered_set>

class Symbol_Table {
public:
    static Scope symbolTableObj;
    static unsigned int scopeLevel;
    static std::unordered_set<std::string> libFunctions;

    static inline bool isLibFunction(std::string name) {
        return Symbol_Table::libFunctions.find(name) != Symbol_Table::libFunctions.end();
    }
};

unsigned int Symbol_Table::scopeLevel = 0;
std::unordered_set<std::string> Symbol_Table::libFunctions = {"print",
                                                              "input",
                                                              "objectmemberkeys",
                                                              "objecttotalmembers",
                                                              "objectcopy",
                                                              "totalarguments",
                                                              "argument",
                                                              "typeof",
                                                              "strtonum",
                                                              "sqrt", "cos", "sin"};

Scope Symbol_Table::symbolTableObj();