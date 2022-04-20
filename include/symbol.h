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

    unsigned int offset;

    friend class Scope;

public:
    Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, unsigned offset);
    Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, unsigned offset, bool isActive);

    std::string to_string();
    ~Symbol();
};

class Variable : public Symbol {
public:
    ScopespaceType space;

public:
    Variable(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, ScopespaceType type, unsigned offset)
        : Symbol(name, scope, line, funcDepth, VARIABLE, offset), space(type) {}
    Variable(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, ScopespaceType type, unsigned offset, bool isActive)
        : Symbol(name, scope, line, funcDepth, VARIABLE, offset, isActive), space(type) {}
};

class Function : public Symbol {
protected:
public:
    Function(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type)
        : Symbol(name, scope, line, funcDepth, type, offset) {}
    Function(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, bool isActive)
        : Symbol(name, scope, line, funcDepth, type, offset, isActive) {}
};

#endif /* __SYMBOL_H */