#include "scope.h"
#include "symbol.h"

#include <algorithm>
#include <list>
#include <string>

void Scope::insert(std::string key, Symbol *symbol, unsigned int scope) {
    hash_table.insert({key, symbol});

    scope_lists[scope].push_front(symbol);
}

void Scope::hide(unsigned int scopeLevel) {
    for (Symbol *symbol : Scope::scope_lists[scopeLevel]) {
        symbol->isActive = false;
    }
}

Symbol *Scope::lookup_scope(std::string key, unsigned int scope) {
    auto scope_list = scope_lists.find(scope);

    if (scope_list != scope_lists.end()) {
        for (auto it : scope_list->second) {
            if (it->isActive && it->name == key) {
                return it;
            }
        }
    }

    return nullptr;
}

auto Scope::lookup_symbol(std::string key) {
    auto p = hash_table.equal_range(key);

    return p;
}

void Scope::clear() {
    hash_table.clear();

    for (auto &list : scope_lists) {
        list.second.clear();
    }

    scope_lists.clear();
}

Symbol *Scope::erase(std::string key) {
    auto p = hash_table.equal_range(key);

    for (auto it = p.first; it != p.second; ++it) {
        if (key == it->second->name) {
        }
    }
}