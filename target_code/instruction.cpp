#include <instruction.h>

#undef FIELD_WIDTH
#define FIELD_WIDTH 15

std::vector<instruction *> instruction_vector;
std::list<incomplete_jump> ij_list;

instruction::instruction(vmopcode op, quad &quad_e) {
    this->opcode = op;

    if (quad_e.arg1)
        this->arg1 = new vmarg(quad_e.arg1);
    else
        this->arg1 = nullptr;

    if (quad_e.arg2)
        this->arg2 = new vmarg(quad_e.arg2);
    else
        this->arg2 = nullptr;

    if (quad_e.result)
        this->result = new vmarg(quad_e.result);
    else
        this->result = nullptr;
}

instruction::instruction(vmopcode op)
    : opcode(op), arg1(nullptr), arg2(nullptr), result(nullptr) {}

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

std::string vmopcode_name[] = {"assign",
                               "add",
                               "sub",
                               "mul",
                               "div",
                               "mod",
                               "uminus",
                               "and",
                               "or",
                               "not",
                               "jump",
                               "jeq",
                               "jne",
                               "jle",
                               "jge",
                               "jlt",
                               "jgt",
                               "call",
                               "pusharg",
                               "funcenter",
                               "funcexit",
                               "newtable",
                               "table_getelem",
                               "table_setelem",
                               "nop"};

static inline void pad_to_width(std::string &str, char pad_char) {
    long pad_size = FIELD_WIDTH - static_cast<long>(str.length());

    for (; pad_size > 0; --pad_size) {
        str += pad_char;
    }
}

std::string target_to_string() {
    std::string result = "";
    std::string field;
    unsigned long i = 0;
    for (auto &target_elem : instruction_vector) {

        field = std::to_string(i++) + ":";
        pad_to_width(field, ' ');
        result += field;

        field = vmopcode_name[target_elem->opcode];
        pad_to_width(field, ' ');
        result += field;

        if (target_elem->arg1) {
            field = target_elem->arg1->to_string();
            pad_to_width(field, ' ');
            result += field;
        }

        if (target_elem->arg2) {
            field = target_elem->arg2->to_string();
            pad_to_width(field, ' ');
            result += field;
        }

        if (target_elem->result) {
            field = target_elem->result->to_string();
            pad_to_width(field, ' ');
            result += field;
        }

        result += "\n";
    }

    return result;
}