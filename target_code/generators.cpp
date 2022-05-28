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
    vmarg *arg1 = new vmarg(q.arg1), *arg2 = new vmarg(q.arg2), *res;

    if (q.label < currProcessedQuad())
        res = new vmarg(instruction_label, quad_vector.at(q.label).taddress);
    else
        ij_list.push_back(incomplete_jump(nextInstructionLabel(), q.label));

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
    instruction *t = new instruction(assign_vmiop, new vmarg(dest_register), nullptr, new vmarg(q.result));

    emit_instruction(t);
}

void FUNCSTART(quad &q) {
    Function *func = dynamic_cast<Function *>(q.result->getSymbol());
    assert(func);
    func->taddress = nextInstructionLabel();
    q.taddress = nextInstructionLabel();

    instruction *t = new instruction(funcenter_vmiop, nullptr, nullptr, new vmarg(q.result));
    emit_instruction(t);
}

void RETURN(quad &q) {
    q.taddress = nextInstructionLabel();
    instruction *t = new instruction(assign_vmiop, new vmarg(q.arg1), nullptr, new vmarg(dest_register));
    emit_instruction(t);
}

void FUNCEND(quad &q) {
    q.taddress = nextInstructionLabel();
    instruction *t = new instruction(funcexit_vmiop, nullptr, nullptr, new vmarg(q.result));
    emit_instruction(t);
}

void generate() {
    std::unordered_map<iopcode, std::function<void(quad &)>> generator_map = {
        {add_iop, ADD},
        {sub_iop, SUB},
        {mul_iop, MUL},
        {div_iop, DIV},
        {mod_iop, MOD},
        {table_create_iop, NEW_TABLE},
        {table_getelem_iop, TABLE_GET_ELEM},
        {table_setelem_iop, TABLE_SET_ELEM},
        {assign_iop, ASSIGN},
        {jump_iop, JUMP},
        {if_eq_iop, IF_EQ},
        {if_not_eq_iop, IF_NOT_EQ},
        {if_greater_iop, IF_GREATER},
        {if_greater_eq_iop, IF_GREATER_EQ},
        {if_less_iop, IF_LESS},
        {if_less_eq_iop, IF_LESS_EQ},
        {param_iop, PARAM},
        {call_iop, CALL},
        {get_retval_iop, GET_RETVAL},
        {funcstart_iop, FUNCSTART},
        {ret_iop, RETURN},
        {funcend_iop, FUNCEND}};

    for (auto &quad : quad_vector) {
        generator_map.at(quad.opcode)(quad);
        processQuad();
    }
}