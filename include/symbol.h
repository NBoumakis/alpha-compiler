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

    friend class Scope;

public:
    Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type);
    Symbol(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, bool isActive);

    virtual std::string to_string() = 0;
    virtual std::string type_string() = 0;

    ~Symbol();
};

class Variable : public Symbol {
public:
    unsigned long offset;
    ScopespaceType space;

public:
    Variable(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, ScopespaceType type, unsigned long offset)
        : Symbol(name, scope, line, funcDepth, VARIABLE), offset(offset), space(type) {}
    Variable(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, ScopespaceType type, unsigned long offset, bool isActive)
        : Symbol(name, scope, line, funcDepth, VARIABLE, isActive), offset(offset), space(type) {}

    std::string to_string() override;
    std::string type_string() override;
};

class Function : public Symbol {
public:
    unsigned long iaddress;
    unsigned long taddress;
    unsigned long totalLocals;

public:
    Function(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, unsigned long offset, unsigned long iaddress)
        : Symbol(name, scope, line, funcDepth, type), iaddress(iaddress) {}
    Function(std::string name, unsigned int scope, unsigned int line, unsigned int funcDepth, SymbolType type, unsigned long offset, unsigned long iaddress, bool isActive)
        : Symbol(name, scope, line, funcDepth, type, isActive), iaddress(iaddress) {}

    std::string to_string() override;
    std::string type_string() override;
};

#endif /* __SYMBOL_H */