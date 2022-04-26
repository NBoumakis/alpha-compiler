#include "scope_space.h"
#include "symbol.h"
#include "symbol_table.h"
#include <string>

static unsigned long tempcounter = 0;

std::string newtempname() {
    return "_t" + tempcounter;
}

void resettemp() {
    tempcounter = 0;
}

Symbol *newTempvar() {
    std::string name = newtempname();
    Symbol *symbol = symbolTableObj.lookup_scope(name, scopeLevel);
    if (symbol == nullptr) {
        symbol = new Variable(name, scopeLevel, 0, funcDepth, currScopespace(), currScopespaceOffset());
        symbolTableObj.insert(name, symbol, scopeLevel);
        return symbol;
    } else {
        return symbol;
    }
}