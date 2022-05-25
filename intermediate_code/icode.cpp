#include "icode.h"
#include "temp_vars.h"
#include <vector>

extern std::vector<quad> quad_vector;

unsigned long loopcounter;
std::stack<unsigned long> loopcounterstack;

void emit(iopcode opcode, exprValue *arg1, exprValue *arg2, exprValue *result,
          unsigned long label, unsigned long line) {
    quad p;

    p.opcode = opcode;
    p.arg1 = arg1;
    p.arg2 = arg2;
    p.result = result;
    p.line = line;
    p.label = label;

    quad_vector.push_back(p);
}

void emit(iopcode opcode, exprValue *arg1, exprValue *arg2, exprValue *result) {
    quad p;

    p.opcode = opcode;
    p.arg1 = arg1;
    p.arg2 = arg2;
    p.result = result;
    p.label = 0;

    quad_vector.push_back(p);
}

void emit(iopcode opcode, unsigned long label) {
    emit(opcode, nullptr, nullptr, nullptr, label, 0);
}

void emit(iopcode opcode, exprValue *arg1, exprValue *arg2, unsigned long label) {
    emit(opcode, arg1, arg2, nullptr, label, 0);
}

void emit(iopcode opcode, exprValue *arg1, exprValue *result) {
    emit(opcode, arg1, nullptr, result, 0, 0);
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
    p.line = 0;
    p.label = 0;

    quad_vector.push_back(p);
}