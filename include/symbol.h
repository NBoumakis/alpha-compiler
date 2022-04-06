#ifndef __SYMBOL_H
#define __SYMBOL_H
#include <string>

enum SymbolType {
    GLOBAL,
    LOCAL,
    FORMAL_ARG,
    USER_FUNC,
    LIB_FUNC
};

class Symbol {
protected:
    std::string name;
    unsigned int scope;
    unsigned int line;
    bool isActive;
    SymbolType type;

    friend class Scope;

public:
    Symbol(std::string name, unsigned int scope, unsigned int line, SymbolType type);
    Symbol(std::string name, unsigned int scope, unsigned int line, SymbolType type, bool isActive);
    ~Symbol();
};

class Variable : protected Symbol {};

class Function : protected Symbol {
protected:
};
#endif