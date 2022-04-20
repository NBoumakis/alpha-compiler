#include "icode.h"

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