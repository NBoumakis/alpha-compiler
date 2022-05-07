#include "scope_space.h"
#include <iostream>
#include <string>

#define FIELD_WIDTH 24

std::vector<quad> quad_vector;

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

unsigned long nextQuadLabel() {
    return quad_vector.size();
}

void patchLabel(unsigned long quadNo, unsigned long label) {
    assert(quadNo < quad_vector.size() && !quad_vector[quadNo].label);

    quad_vector[quadNo].label = label;
}

void patchList(unsigned long list, unsigned long label) {
    while (list) {
        unsigned long next = quad_vector[list].label;
        quad_vector[list].label = label;
        list = next;
    }
}

std::string opcode_name[] = {"assign", "add", "sub", "mul", "div", "mod", "uminus", "and", "or", "not", "if_eq", "if_not_eq", "if_less_eq", "if_greater_eq", "if_less", "if_greater", "jump", "call", "param", "ret", "get_retval", "funcstart", "funcend", "table_create", "table_getelem", "table_setelem"};

static inline void pad_to_width(std::string &str, char pad_char) {
    long pad_size = FIELD_WIDTH - static_cast<long>(str.length());

    for (; pad_size > 0; --pad_size) {
        str += pad_char;
    }
}

std::string quad_to_string() {
    std::string result = "";
    std::string field;
    for (size_t i = 1; i < quad_vector.size(); ++i) {
        auto &quad_elem = quad_vector[i];

        field = std::to_string(i) + ":";
        pad_to_width(field, ' ');
        result += field;

        field = opcode_name[quad_elem.opcode];
        pad_to_width(field, ' ');
        result += field;

        if (quad_elem.arg1) {
            field = quad_elem.arg1->to_string();
            pad_to_width(field, ' ');
            result += field;
        } else {
            field = "";
            pad_to_width(field, ' ');
            result += field;
        }

        if (quad_elem.arg2) {
            field = quad_elem.arg2->to_string();
            pad_to_width(field, ' ');
            result += field;
        } else {
            field = "";
            pad_to_width(field, ' ');
            result += field;
        }

        if (quad_elem.result) {
            field = quad_elem.result->to_string();
            pad_to_width(field, ' ');
            result += field;
        } else {
            field = "";
            pad_to_width(field, ' ');
            result += field;
        }

        if (quad_elem.label)
            result += std::to_string(quad_elem.label);

        result += "\r\n";
    }

    return result;
}