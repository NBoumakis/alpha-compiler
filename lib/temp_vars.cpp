#include "scope_space.h"
#include "symbol.h"
#include "symbol_table.h"
#include <string>

extern int yylineno;
static unsigned long tempcounter = 0;

std::string newtempname() {
    return "_t" + std::to_string(tempcounter++);
}

void resettemp() {
    tempcounter = 0;
}

Symbol *newTempvar() {
    std::string name = newtempname();
    Symbol *symbol = symbolTableObj.lookup_scope(name, scopeLevel);
    if (symbol == nullptr) {
        symbol = new Variable(name, scopeLevel, yylineno, funcDepth, currScopespace(), currScopespaceOffset());
        symbolTableObj.insert(name, symbol, scopeLevel);
        increaseCurrScopeOffset();
        return symbol;
    } else {
        return symbol;
    }
}