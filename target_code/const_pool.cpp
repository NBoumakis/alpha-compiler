#include "const_pool.h"

std::vector<std::string> string_pool;
std::vector<double> number_pool;
std::vector<std::string> libfunc_pool;
std::vector<Function *> userfunc_pool;

unsigned long const_newstring(const std::string &str) {
    string_pool.push_back(str);

    return string_pool.size();
}

unsigned long const_newnumber(const double num) {
    number_pool.push_back(num);

    return number_pool.size();
}

unsigned long libfunc_newused(const std::string &name) {
    libfunc_pool.push_back(name);

    return libfunc_pool.size();
}

unsigned long userfunc_newused(Function *const &func) {
    userfunc_pool.push_back(func);

    return number_pool.size();
}
