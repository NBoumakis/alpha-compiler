#include "types.h"
#include <cassert>
#include <iostream>

std::string exprValue::to_string() {
    assert(this);

    switch (this->valType) {
    case varExpr_T:
    case TableitemExpr_T:
    case newtableExpr_T:
    case arithmexprExpr_T:
    case boolexprExpr_T:
    case assignexprExpr_T:
    case userfuncExpr_T:
    case libfuncExpr_T:
        return this->symbolVal->name;

    case constnumExpr_T:
        return std::to_string(this->numConstval);

    case constboolExpr_T:
        return ((this->boolConstVal) ? "true" : "false");

    case conststringExpr_T:
        return "\"" + this->strConstVal + "\"";

    case nilExpr_T:
        return "nil";

    case InvalidExpr_T:
        return "invalid";

    default:
        assert(false);
    }
}

std::string exprValue::type_string() {
    assert(this);

    std::string type_names[] = {"variable",
                                "table item",
                                "user function",
                                "library function",
                                "arithmetic expression",
                                "boolean expression",
                                "assignment expression",
                                "new table",
                                "constant number",
                                "constant boolean",
                                "constant string",
                                "nil",
                                "invalid"};

    return type_names[this->valType];
}

exprValue::operator bool() const {
    assert(this);

    switch (this->valType) {
    case userfuncExpr_T:
    case libfuncExpr_T:
    case newtableExpr_T:
        return true;

    case constnumExpr_T:
        return this->numConstval != 0;

    case constboolExpr_T:
        return this->boolConstVal;

    case conststringExpr_T:
        return this->strConstVal != "";

    case nilExpr_T:
        return false;

    default:
        assert(false);
    }
}