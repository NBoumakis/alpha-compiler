#include "symbol.h"
#include <cassert>
#include <string>

Symbol::Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type)
    : name(name), scope(scope), line(line), funcDepth(funcDepth), isActive(true), type(type) {}

Symbol::Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, bool isActive)
    : name(name), scope(scope), line(line), funcDepth(funcDepth), isActive(isActive), type(type) {}

std::string Variable::to_string() {
    std::string result;

    result += "\"" + name + "\"\t";
    result += "[variable]\t\t";

    result += "(line " + std::to_string(line) + ")\t";
    result += "(scope " + std::to_string(scope) + ")";
    result += "(offset " + std::to_string(offset) + ")";

    return result;
}

std::string Function::to_string() {
    std::string result;

    result += "\"" + name + "\"\t";

    if (type == USER_FUNC) {
        result += "[user function]\t\t";
    } else {
        result += "[library function]\t\t";
    }

    result += "(line " + std::to_string(line) + ")\t";
    result += "(scope " + std::to_string(scope) + ")";

    return result;
}

Symbol::~Symbol() {}
