#ifndef __SCOPESPACE_H
#define __SCOPESPACE_H

#include "icode.h"
#include "symbol.h"
#include <cassert>
#include <stack>
#include <vector>

extern std::vector<quad> quad_vector;

extern unsigned long programVarOffset;
extern unsigned long functionLocalOffset;
extern unsigned long formalArgOffset;
extern unsigned long scopespaceCounter;

extern std::stack<unsigned long> scopeOffsetStack;

ScopespaceType currScopespace();

unsigned long currScopespaceOffset();

void increaseCurrScopeOffset();
void enterScopespace();

void exitScopespace();

void resetFunctionLocalOffset();

void resetFormalArgOffset();

void restoreCurrScopeOffset(unsigned long n);

unsigned long nextQuadLabel();

void patchLabel(unsigned long quadNo, unsigned long label);

void patchList(unsigned long list, unsigned long label);

std::string quad_to_string();

#endif /* __SCOPESPACE_H */