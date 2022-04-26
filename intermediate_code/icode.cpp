#include "icode.h"
#include "temp_vars.h"

extern std::vector<quad> quad_vector;

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

    quad_vector.push_back(p);
}

exprValue *emit_iftableitem(exprValue *expr) {
    if (expr->valType != TableitemExpr_T) {
        return expr;
    } else {
        exprValue *result = new exprValue();
        result->valType = varExpr_T;
        result->symbolVal = newTempvar();
        emit(table_getelem_iop, expr, expr->indexVal, result);

        return result;
    }
}