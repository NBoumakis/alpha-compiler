#ifndef __SYMBOL_H
#define __SYMBOL_H

#include <string>

enum SymbolType {
    GLOBAL_VAR,
    LOCAL_VAR,
    FORMAL_ARG,
    USER_FUNC,
    LIB_FUNC
};

class Symbol {
public:
    std::string name;
    unsigned int scope;
    unsigned int line;
    unsigned int funcDepth;
    bool isActive;
    SymbolType type;

    friend class Scope;

public:
    Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type);
    Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, bool isActive);

    std::string to_string();
    ~Symbol();
};

class Variable : public Symbol {
public:
    Variable(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type) : Symbol(name, scope, line, funcDepth, type) {}
    Variable(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, bool isActive) : Symbol(name, scope, line, funcDepth, type, isActive) {}
};

class Function : public Symbol {
protected:
public:
    Function(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type) : Symbol(name, scope, line, funcDepth, type) {}
    Function(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, bool isActive) : Symbol(name, scope, line, funcDepth, type, isActive) {}
};

#endif /* __SYMBOL_H */