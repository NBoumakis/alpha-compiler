#include "../include/scope.h"
#include "../include/symbol.h"

#include <list>
#include <string>

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
