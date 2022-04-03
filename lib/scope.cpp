#include "../include/scope.h"
#include "../include/symbol.h"

void Scope::insert(std::string key, Symbol *symbol, unsigned int scope){
    Scope::hash_table.insert({key,symbol});
    Scope::scope_lists[scope].push_front(symbol);
}
    
    
void Scope::hide(unsigned int scopeLevel){
    for (Symbol* symbol : Scope::scope_lists[scopeLevel]){
        symbol->isActive=false;
    }
}