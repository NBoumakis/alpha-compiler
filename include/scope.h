#ifndef __SCOPE_H
#define __SCOPE_H

#include "symbol.h"
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

class Scope {
private:
    std::unordered_multimap<std::string, Symbol *> hash_table;
    std::vector<std::list<Symbol *>> scope_lists;

public:
    Scope();
    ~Scope();

    void insert(std::string key, Symbol *symbol, unsigned int scope);
    void hide(unsigned int scopeLevel);
    Symbol *lookup_scope(std::string key, unsigned int scope);
    Symbol *lookup_symbol(std::string key);
    /* Iterate over */
    Symbol *erase(std::string key);
    void clear();
};

#endif /* __SCOPE_H */