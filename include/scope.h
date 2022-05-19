#ifndef __SCOPE_H
#define __SCOPE_H

#include "symbol.h"
#include <list>
#include <map>
#include <string>
#include <unordered_map>

class Scope {
private:
    std::unordered_multimap<std::string, Symbol *> hash_table;
    std::map<unsigned int, std::list<Symbol *>> scope_lists;

public:
    void insert(std::string key, Symbol *symbol, unsigned int scope);
    void hide(unsigned int scopeLevel);
    Symbol *lookup_scope(std::string key, unsigned int scope);
    auto lookup_symbol(std::string key);
    void get_symbols_scope_order();
    Symbol *erase(std::string key);
    void clear();
};

#endif /* __SCOPE_H */