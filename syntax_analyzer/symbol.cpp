#include "symbol.h"
#include <string>

Symbol::Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, enum SymbolType type)
    : name(name), scope(scope), line(line), funcDepth(funcDepth), type(type), isActive(true) {}

Symbol::Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, enum SymbolType type, bool isActive)
    : name(name), scope(scope), line(line), funcDepth(funcDepth), type(type), isActive(isActive) {}

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
    case FORMAL_ARG:
        result += "[formal argument]\t\t";
        break;
    case LOCAL_VAR:
        result += "[local variable]\t\t";
        break;
    case GLOBAL_VAR:
        result += "[global variable]\t\t";
        break;

    default:
        result += "Error, this is impossible";
        break;
    }

    result += "(line " + std::to_string(line) + ")\t";
    result += "(scope " + std::to_string(scope) + ")";

    return result;
}

Symbol::~Symbol() {}
