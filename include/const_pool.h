#ifndef __CONST_POOL_H
#define __CONST_POOL_H

#include <string>
#include <vector>

extern std::vector<std::string> string_pool;
extern std::vector<double> number_pool;
extern std::vector<std::string> libfunc_pool;

unsigned long const_newstring(const std::string &);
unsigned long const_newnumber(const double);
unsigned long libfunc_newused(const std::string &);

#endif /* __CONST_POOL_H */