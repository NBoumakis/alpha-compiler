#ifndef __SCOPESPACE_H
#define __SCOPESPACE_H

#include "icode.h"
#include "symbol.h"
#include <stack>
#include <vector>

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

#endif /* __SCOPESPACE_H */