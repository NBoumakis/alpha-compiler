#include "../include/symbol.h"
#include <string>

Symbol::Symbol(std::string name, unsigned int scope, unsigned int line, enum SymbolType type)
    : name(name), scope(scope), line(line), type(type), isActive(true) {}

Symbol::Symbol(std::string name, unsigned int scope, unsigned int line, enum SymbolType type, bool isActive)
    : name(name), scope(scope), line(line), type(type), isActive(isActive) {}

Symbol::~Symbol() {}
