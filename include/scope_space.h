#ifndef __SCOPESPACE_H
#define __SCOPESPACE_H

#include "symbol.h"
#include <cassert>
unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopespaceCounter = 1;

ScopespaceType currScopespace() {
    if (scopespaceCounter == 1) {
        return GLOBAL_VAR;
    } else if (scopespaceCounter % 2 == 0) {
        return FORMAL_ARG;
    } else {
        return LOCAL_VAR;
    }
}

unsigned currScopespaceOffset() {
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

#endif /* __SCOPESPACE_H */