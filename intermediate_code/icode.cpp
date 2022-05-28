#include "icode.h"
#include "temp_vars.h"
#include <cassert>
#include <vector>

std::vector<quad> quad_vector;

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
    p.label = label;

    quad_vector.push_back(p);
}

exprValue *emit_iftableitem(exprValue *expr, bool assign) {
    if (!expr->isTableitem()) {
        return expr;
    } else {
        exprValue *result;

        if (assign) {
            result = new exprValue(assignexprExpr_T);
        } else {
            result = new exprValue(varExpr_T);
        }

        result->setSymbol(newTempvar());
        emit(table_getelem_iop, result, expr, expr->getIndex());

        return result;
    }
}

void init_quad_vector() {
    quad p;

    p.opcode = nop_iop;
    p.arg1 = nullptr;
    p.arg2 = nullptr;
    p.result = nullptr;
    p.label = 0;

    quad_vector.push_back(p);
}

unsigned long nextQuadLabel() {
    return quad_vector.size();
}

void patchLabel(unsigned long quadNo, unsigned long label) {
    assert(quadNo < quad_vector.size() && !quad_vector.at(quadNo).label);

    quad_vector.at(quadNo).label = label;
}

void patchList(unsigned long list, unsigned long label) {
    while (list) {
        unsigned long next = quad_vector.at(list).label;
        quad_vector.at(list).label = label;
        list = next;
    }
}

std::string opcode_name[] = {"assign", "add", "sub", "mul", "div", "mod", "and", "or", "if_eq", "if_not_eq", "if_less_eq", "if_greater_eq", "if_less", "if_greater", "jump", "call", "param", "ret", "get_retval", "funcstart", "funcend", "table_create", "table_getelem", "table_setelem", "nop"};

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
        auto &quad_elem = quad_vector.at(i);

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

        result += "\n";
    }

    return result;
}