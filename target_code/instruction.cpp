#include <instruction.h>

std::vector<instruction *> instruction_vector;
std::list<incomplete_jump> ij_list;

instruction::instruction(vmopcode op, quad &quad_e) {
    this->opcode = op;

    this->arg1 = new vmarg(quad_e.arg1);
    this->arg2 = new vmarg(quad_e.arg2);
    this->result = new vmarg(quad_e.result);
}

instruction::instruction(vmopcode op)
    : opcode(op) {}

instruction::instruction(vmopcode op, vmarg *arg1, vmarg *arg2, vmarg *result)
    : opcode(op), arg1(arg1), arg2(arg2), result(result) {}

void patchIncompleteJumps() {
    for (auto &jump : ij_list) {
        if (jump.iaddress == quad_vector.size()) {
            vmarg *target = new vmarg(instruction_label, instruction_vector.size());
            instruction_vector.at(jump.instrNo)->result = target;
        } else {
            vmarg *target = new vmarg(instruction_label, quad_vector.at(jump.iaddress).taddress);
            instruction_vector.at(jump.instrNo)->result = target;
        }
    }
}

void emit_instruction(instruction *const &instr) {
    instruction_vector.push_back(instr);
}

unsigned long nextInstructionLabel() {
    return instruction_vector.size();
}