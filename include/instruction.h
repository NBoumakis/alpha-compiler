#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include "icode.h"
#include "vmarg.h"
#include <list>
#include <vector>

class instruction;
class incomplete_jump;

extern std::vector<instruction *> instruction_vector;
extern std::list<incomplete_jump> ij_list;

enum vmopcode {
    assign_vmiop,
    add_vmiop,
    sub_vmiop,
    mul_vmiop,
    div_vmiop,
    mod_vmiop,
    uminus_vmiop,
    and_vmiop,
    or_vmiop,
    not_vmiop,
    jump_vmiop,
    jeq_vmiop,
    jne_vmiop,
    jle_vmiop,
    jge_vmiop,
    jlt_vmiop,
    jgt_vmiop,
    call_vmiop,
    pusharg_vmiop,
    funcenter_vmiop,
    funcexit_vmiop,
    newtable_vmiop,
    table_getelem_vmiop,
    table_setelem_vmiop,
    nop_vmiop
};

class instruction {
public:
    vmopcode opcode;
    vmarg *arg1;
    vmarg *arg2;
    vmarg *result;
    unsigned long srcLine;

    friend void patchIncompleteJumps();

    instruction(vmopcode);
    instruction(vmopcode, quad &);
    instruction(vmopcode, vmarg *, vmarg *, vmarg *);
};

class incomplete_jump {
    unsigned long instrNo;
    unsigned long iaddress;

    friend void patchIncompleteJumps();

public:
    incomplete_jump(unsigned long instrNo, unsigned long iaddress) : instrNo(instrNo),
                                                                     iaddress(iaddress) {}
};

void patchIncompleteJumps();

unsigned long nextInstructionLabel();

void emit_instruction(instruction *const &);

std::string target_to_string();

#endif /* __INSTRUCTION_H */