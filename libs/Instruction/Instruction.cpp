#include <iostream>

#include "Instruction.h"

Instruction::Instruction (void)
{
    this->PC = "0x0";
    this->tag = 0;
    this->op_type = 0;

    this->src_reg1 = -1;
    this->src_reg1_ready = true;
    this->src_reg1_val = -1;
    
    this->src_reg2 = -1;
    this->src_reg2_ready = true;
    this->src_reg2_val;
    
    this->dest_reg = -1;
    this->dest_reg_ready = true;
    this->dest_reg_val = -1;

    this->IF[0] = 0;
    this->IF[1] = 0;

    this->ID[0] = 0;
    this->ID[1] = 0;

    this->IS[0] = 0;
    this->IS[1] = 0;

    this->EX[0] = 0;
    this->EX[1] = 0;

    this->WB[0] = 0;
    this->WB[1] = 0;

    this->state = "IF";
}

std::ostream& operator << (std::ostream &output, Instruction instr)
{
    output << instr.tag << " ";
    output << "fu{" << instr.op_type << "} ";
    output << "src{" << instr.src_reg1 << "," << instr.src_reg2 << "} ";
    output << "dst{" << instr.dest_reg << "} ";
    output << "IF{" << instr.IF[0] << "," << instr.IF[1] << "} ";
    output << "ID{" << instr.ID[0] << "," << instr.ID[1] << "} ";
    output << "IS{" << instr.IS[0] << "," << instr.IS[1] << "} ";
    output << "EX{" << instr.EX[0] << "," << instr.EX[1] << "} ";
    output << "WB{" << instr.WB[0] << "," << instr.WB[1] << "}\n";
    return output;
}
