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
    result += "[" + type_string() + "]\t\t";

    result += "(line " + std::to_string(line) + ")\t";
    result += "(scope " + std::to_string(scope) + ")";
    result += "(offset " + std::to_string(offset) + ")";

    return result;
}

std::string Variable::type_string() {
    assert(this);

    switch (this->space) {
    case GLOBAL_VAR:
        return "global variable";

    case LOCAL_VAR:
        return "local variable";

    case FORMAL_ARG:
        return "formal argument";

    default:
        assert(false);
    }
}

std::string Function::to_string() {
    std::string result;

    result += "\"" + name + "\"\t";

    result += "[" + type_string() + "]\t\t";

    result += "(line " + std::to_string(line) + ")\t";
    result += "(scope " + std::to_string(scope) + ")";

    return result;
}

std::string Function::type_string() {
    assert(this);

    switch (this->type) {
    case USER_FUNC:
        return "user function";

    case LIB_FUNC:
        return "library function";

    default:
        assert(false);
    }
}

Symbol::~Symbol() {}
