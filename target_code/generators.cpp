#include "generators.h"
#include "instruction.h"

static unsigned long processedQuad = 0;

unsigned long currProcessedQuad() {
    return processedQuad;
}

void processQuad() {
    ++processedQuad;
}

void generate(vmopcode op, quad &quad_e) {
    instruction *t = new instruction(op, quad_e);

    quad_e.taddress = nextInstructionLabel();
    emit_instruction(t);
}

void generate_relational(vmopcode op, quad &q) {
    vmarg *arg1 = new vmarg(q.arg1), *arg2 = new vmarg(q.arg2), *res;

    if (q.label < currProcessedQuad())
        res = new vmarg(instruction_label, quad_vector.at(q.label).taddress);
    else
        add_incomplete_jump(nextInstructionLabel(), q.label);

    instruction *t = new instruction(op, arg1, arg2, res);

    q.taddress = nextInstructionLabel();
    emit_instruction(t);
}

void ADD(quad &q) {
    generate(add_vmiop, q);
}

void SUB(quad &q) {
    generate(sub_vmiop, q);
}

void MUL(quad &q) {
    generate(mul_vmiop, q);
}

void DIV(quad &q) {
    generate(div_vmiop, q);
}

void MOD(quad &q) {
    generate(mod_vmiop, q);
}

void NEW_TABLE(quad &q) {
    generate(newtable_vmiop, q);
}

void TABLE_GET_ELEM(quad &q) {
    generate(table_getelem_vmiop, q);
}

void TABLE_SET_ELEM(quad &q) {
    generate(table_setelem_vmiop, q);
}

void ASSIGN(quad &q) {
    generate(assign_vmiop, q);
}

void NOP(quad &q) {
    instruction *t = new instruction(nop_vmiop);

    emit_instruction(t);
}

void JUMP(quad &q) {
}
void IF_EQ(quad &q);
void IF_NOT_EQ(quad &q);
void IF_GREATER(quad &q);
void IF_GREATER_EQ(quad &q);
void IF_LESS(quad &q);
void IF_LESS_EQ(quad &q);
void NOT(quad &q);
void OR(quad &q);
void PARAM(quad &q);
void CALL(quad &q);
void GET_RETVAL(quad &q);
void FUNCSTART(quad &q);
void RETURN(quad &q);
void FUNCEND(quad &q);
