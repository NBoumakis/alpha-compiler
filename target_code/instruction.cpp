#include <instruction.h>

std::vector<instruction *> instruction_vector;

instruction::instruction(vmopcode op, quad &quad_e) {
    this->opcode = op;

    this->arg1 = vmarg(quad_e.arg1);
    this->arg2 = vmarg(quad_e.arg2);
    this->result = vmarg(quad_e.result);
}

instruction::instruction(vmopcode op) {
    this->opcode = op;
}

void emit_instruction(instruction *const &instr) {
    instruction_vector.push_back(instr);
}

unsigned long nextInstructionLabel() {
    return instruction_vector.size();
}
