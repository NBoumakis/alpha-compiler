#include "const_pool.h"

bimap<std::string> string_pool;
bimap<double> number_pool;
bimap<std::string> libfunc_pool;
bimap<Function *> userfunc_pool;

unsigned long const_newstring(const std::string &str) {
    return string_pool.insert(str);
}

unsigned long const_newnumber(const double num) {
    return number_pool.insert(num);
}

unsigned long libfunc_newused(const std::string &name) {
    return libfunc_pool.insert(name);
}

unsigned long userfunc_newused(Function *const &func) {
    userfunc_pool.insert(func);

    return func->taddress;
}
