#include "scope_space.h"
#include <cassert>
#include <string>

unsigned long programVarOffset = 0;
unsigned long functionLocalOffset = 0;
unsigned long formalArgOffset = 0;
unsigned long scopespaceCounter = 1;

std::stack<unsigned long> scopeOffsetStack;

ScopespaceType currScopespace() {
    if (scopespaceCounter == 1) {
        return GLOBAL_VAR;
    } else if (scopespaceCounter % 2 == 0) {
        return FORMAL_ARG;
    } else {
        return LOCAL_VAR;
    }
}

unsigned long currScopespaceOffset() {
    switch (currScopespace()) {
    case GLOBAL_VAR:
        return programVarOffset;
    case LOCAL_VAR:
        return functionLocalOffset;
    case FORMAL_ARG:
        return formalArgOffset;

    default:
        assert(false);
    }
}

void increaseCurrScopeOffset() {
    switch (currScopespace()) {
    case GLOBAL_VAR:
        ++programVarOffset;
        break;
    case LOCAL_VAR:
        ++functionLocalOffset;
        break;
    case FORMAL_ARG:
        ++formalArgOffset;
        break;

    default:
        assert(false);
    }
}

void enterScopespace() {
    ++scopespaceCounter;
}

void exitScopespace() {
    assert(scopespaceCounter > 1);
    --scopespaceCounter;
}

void resetFunctionLocalOffset() {
    functionLocalOffset = 0;
}

void resetFormalArgOffset() {
    formalArgOffset = 0;
}

void restoreCurrScopeOffset(unsigned long n) {
    switch (currScopespace()) {
    case GLOBAL_VAR:
        programVarOffset = n;
        break;

    case LOCAL_VAR:
        functionLocalOffset = n;
        break;

    case FORMAL_ARG:
        formalArgOffset = n;
        break;

    default:
        assert(false);
    }
}
