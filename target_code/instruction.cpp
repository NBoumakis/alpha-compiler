#include <instruction.h>

instruction::instruction(vmopcode op, quad &quad_e) {
    this->opcode = op;

    this->arg1 = vmarg(quad_e.arg1);
    this->arg2 = vmarg(quad_e.arg2);
    this->result = vmarg(quad_e.result);
}