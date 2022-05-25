#include "icode.h"
#include "temp_vars.h"
#include <vector>

extern std::vector<quad> quad_vector;

unsigned long loopcounter;
std::stack<unsigned long> loopcounterstack;

void emit(iopcode opcode, exprValue *arg1, exprValue *arg2, exprValue *result) {
    quad p;

    p.opcode = opcode;
    p.arg1 = arg1;
    p.arg2 = arg2;
    p.result = result;
    p.label = 0;

    quad_vector.push_back(p);
}

void emit(iopcode opcode, exprValue *arg1, exprValue *arg2, unsigned long label) {
    quad p;

    p.opcode = opcode;
    p.arg1 = arg1;
    p.arg2 = arg2;
    p.result = nullptr;
    p.label = 0;

    quad_vector.push_back(p);
}

exprValue *emit_iftableitem(exprValue *expr, bool assign) {
    if (!expr->isTableitem()) {
        return expr;
    } else {
        exprValue *result;

        if (assign) {
            result = new exprValue(varExpr_T);
        } else {
            result = new exprValue(assignexprExpr_T);
        }

        result->setSymbol(newTempvar());
        emit(table_getelem_iop, result, expr, expr->getIndex());

        return result;
    }
}

void init_quad_vector() {
    quad p;

    p.arg1 = nullptr;
    p.arg2 = nullptr;
    p.result = nullptr;
    p.label = 0;

    quad_vector.push_back(p);
}