#include "../include/scope.h"
#include "../include/symbol.h"

#include <algorithm>
#include <list>
#include <string>

void Scope::insert(std::string key, Symbol *symbol, unsigned int scope) {
    Scope::hash_table.insert({key, symbol});
    Scope::scope_lists[scope].push_front(symbol);
}

void Scope::hide(unsigned int scopeLevel) {
    for (Symbol *symbol : Scope::scope_lists[scopeLevel]) {
        symbol->isActive = false;
    }
}

Symbol *Scope::lookup_scope(std::string key, unsigned int scope) {
    std::list<Symbol *> scope_list = scope_lists[scope];

    for (Symbol *it : scope_list) {
        if (it->name == key) {
            return it;
        }
    }

    return nullptr;
}

Symbol *Scope::lookup_symbol(std::string key) {
    auto p = hash_table.equal_range(key);

    for (auto it = p.first; it != p.second; ++it) {
        if (key == it->second->name) {
            return it->second;
        }
    }

    return nullptr;
}

void Scope::clear() {
    hash_table.clear();
    for (auto &&i : scope_lists) {
        i.clear();
    }
    scope_lists.clear();
}