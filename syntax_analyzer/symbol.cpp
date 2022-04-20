#include "symbol.h"
#include <cassert>
#include <string>

Symbol::Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, unsigned long offset)
    : name(name), scope(scope), line(line), funcDepth(funcDepth), type(type), isActive(true), offset(offset) {}

Symbol::Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, unsigned long offset, bool isActive)
    : name(name), scope(scope), line(line), funcDepth(funcDepth), type(type), isActive(isActive), offset(offset) {}

std::string Symbol::to_string() {
    std::string result;

    result += "\"" + name + "\"\t";

    switch (type) {
    case LIB_FUNC:
        result += "[library function]\t\t";
        break;
    case USER_FUNC:
        result += "[user function]\t\t";
        break;
    case VARIABLE:
        result += "[variable]\t\t";
        break;

    default:
        assert(false);
        break;
    }

    result += "(line " + std::to_string(line) + ")\t";
    result += "(scope " + std::to_string(scope) + ")";

    return result;
}

Symbol::~Symbol() {}
