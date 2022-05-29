#include "generators.h"
#include "const_pool.h"
#include "instruction.h"
#include <cassert>
#include <functional>
#include <unordered_map>

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
    instruction *t;

    if (q.label < currProcessedQuad()) {
        vmarg *arg1 = (q.arg1) ? new vmarg(q.arg1) : nullptr;
        vmarg *arg2 = (q.arg2) ? new vmarg(q.arg2) : nullptr;
        vmarg *res = new vmarg(instruction_label, quad_vector.at(q.label).taddress);
        t = new instruction(op, arg1, arg2, res);
    } else {
        ij_list.push_back(incomplete_jump(nextInstructionLabel(), q.label));
        t = new instruction(op, q);
    }

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
    generate_relational(jump_vmiop, q);
}

void IF_EQ(quad &q) {
    generate_relational(jeq_vmiop, q);
}

void IF_NOT_EQ(quad &q) {
    generate_relational(jne_vmiop, q);
}

void IF_GREATER(quad &q) {
    generate_relational(jgt_vmiop, q);
}

void IF_GREATER_EQ(quad &q) {
    generate_relational(jeq_vmiop, q);
}

void IF_LESS(quad &q) {
    generate_relational(jlt_vmiop, q);
}

void IF_LESS_EQ(quad &q) {
    generate_relational(jle_vmiop, q);
}

void PARAM(quad &q) {
    q.taddress = nextInstructionLabel();
    instruction *t = new instruction(pusharg_vmiop, new vmarg(q.arg1), nullptr, nullptr);

    emit_instruction(t);
}

void CALL(quad &q) {

    q.taddress = nextInstructionLabel();
    instruction *t = new instruction(call_vmiop, new vmarg(q.arg1), nullptr, nullptr);

    emit_instruction(t);
}

void GET_RETVAL(quad &q) {
    q.taddress = nextInstructionLabel();
    instruction *t = new instruction(assign_vmiop, new vmarg(q.arg1), new vmarg(retval), nullptr);

    emit_instruction(t);
}

void FUNCSTART(quad &q) {
    Function *func = dynamic_cast<Function *>(q.arg1->getSymbol());
    assert(func);
    func->taddress = nextInstructionLabel();
    q.taddress = nextInstructionLabel();

    instruction *t = new instruction(funcenter_vmiop, q);
    emit_instruction(t);
}

void RETURN(quad &q) {
    q.taddress = nextInstructionLabel();
    instruction *t = new instruction(assign_vmiop, new vmarg(q.arg1), new vmarg(retval), nullptr);
    emit_instruction(t);
}

void FUNCEND(quad &q) {
    q.taddress = nextInstructionLabel();
    instruction *t = new instruction(funcexit_vmiop, q);
    emit_instruction(t);
}

void generate_target_code() {
    std::unordered_map<iopcode, std::function<void(quad &)>> generator_map = {
        {assign_iop, ASSIGN},
        {add_iop, ADD},
        {sub_iop, SUB},
        {mul_iop, MUL},
        {div_iop, DIV},
        {mod_iop, MOD},
        {if_eq_iop, IF_EQ},
        {if_not_eq_iop, IF_NOT_EQ},
        {if_greater_iop, IF_GREATER},
        {if_greater_eq_iop, IF_GREATER_EQ},
        {if_less_iop, IF_LESS},
        {if_less_eq_iop, IF_LESS_EQ},
        {jump_iop, JUMP},
        {call_iop, CALL},
        {param_iop, PARAM},
        {ret_iop, RETURN},
        {get_retval_iop, GET_RETVAL},
        {funcstart_iop, FUNCSTART},
        {funcend_iop, FUNCEND},
        {table_create_iop, NEW_TABLE},
        {table_getelem_iop, TABLE_GET_ELEM},
        {table_setelem_iop, TABLE_SET_ELEM},
        {nop_iop, NOP}};

    for (auto &quad : quad_vector) {
        generator_map.at(quad.opcode)(quad);
        processQuad();
    }

    patchIncompleteJumps();
}