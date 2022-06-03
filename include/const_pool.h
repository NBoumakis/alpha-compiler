#ifndef __CONST_POOL_H
#define __CONST_POOL_H

#include "bimap.h"
#include "symbol.h"
#include <string>
#include <vector>

extern bimap<std::string> string_pool;
extern bimap<double> number_pool;
extern bimap<std::string> libfunc_pool;
extern bimap<Function *> userfunc_pool;

unsigned long const_newstring(const std::string &);
unsigned long const_newnumber(const double);
unsigned long libfunc_newused(const std::string &);
unsigned long userfunc_newused(Function *const &func);

#endif /* __CONST_POOL_H */