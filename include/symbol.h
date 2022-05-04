#ifndef __SYMBOL_H
#define __SYMBOL_H

#include <string>

enum SymbolType {
    VARIABLE,
    USER_FUNC,
    LIB_FUNC
};

enum ScopespaceType {
    GLOBAL_VAR,
    LOCAL_VAR,
    FORMAL_ARG
};

class Symbol {
public:
    std::string name;
    unsigned int scope;
    unsigned int line;
    unsigned int funcDepth;
    bool isActive;

    SymbolType type;

    unsigned long offset;

    friend class Scope;

public:
    Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, unsigned long offset);
    Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, unsigned long offset, bool isActive);

    std::string to_string();
    ~Symbol();
};

class Variable : public Symbol {
public:
    ScopespaceType space;

public:
    Variable(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, ScopespaceType type, unsigned long offset)
        : Symbol(name, scope, line, funcDepth, VARIABLE, offset), space(type) {}
    Variable(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, ScopespaceType type, unsigned long offset, bool isActive)
        : Symbol(name, scope, line, funcDepth, VARIABLE, offset, isActive), space(type) {}
};

class Function : public Symbol {
public:
    unsigned long iaddress;
    unsigned long totalLocals;

public:
    Function(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, unsigned long offset, unsigned long iaddress)
        : Symbol(name, scope, line, funcDepth, type, offset), iaddress(iaddress) {}
    Function(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, unsigned long offset, unsigned long iaddress, bool isActive)
        : Symbol(name, scope, line, funcDepth, type, offset, isActive), iaddress(iaddress) {}
};

#endif /* __SYMBOL_H */