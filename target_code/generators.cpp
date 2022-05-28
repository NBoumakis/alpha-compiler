#include "generators.h"
#include "instruction.h"

void generate(vmopcode op, quad &quad_e) {
    instruction *t = new instruction(op, quad_e);

    quad_e.taddress = nextInstructionLabel();
    emit_instruction(t);
}

void ADD(quad &);
void SUB(quad &);
void MUL(quad &);
void DIV(quad &);
void MOD(quad &);
void NEW_TABLE(quad &);
void TABLE_GET_ELEM(quad &);
void TABLE_SET_ELEM(quad &);
void ASSIGN(quad &);
void NOP(quad &);
void JUMP(quad &);
void IF_EQ(quad &);
void IF_NOT_EQ(quad &);
void IF_GREATER(quad &);
void IF_GREATER_EQ(quad &);
void IF_LESS(quad &);
void IF_LESS_EQ(quad &);
void NOT(quad &);
void OR(quad &);
void PARAM(quad &);
void CALL(quad &);
void GET_RETVAL(quad &);
void FUNCSTART(quad &);
void RETURN(quad &);
void FUNCEND(quad &);
