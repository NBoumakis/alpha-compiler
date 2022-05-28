#ifndef __CONST_POOL_H
#define __CONST_POOL_H

#include "symbol.h"
#include <string>
#include <vector>

extern std::vector<std::string> string_pool;
extern std::vector<double> number_pool;
extern std::vector<std::string> libfunc_pool;
extern std::vector<Function *> userfunc_pool;

unsigned long const_newstring(const std::string &);
unsigned long const_newnumber(const double);
unsigned long libfunc_newused(const std::string &);
unsigned long userfunc_newused(Function *const &func);

#endif /* __CONST_POOL_H */