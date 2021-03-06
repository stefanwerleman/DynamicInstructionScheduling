#ifndef INSTRUCTION
#define INSTRUCTION

#include <iostream>
#include <string>

// This is just a carrier for all the traces but will still be dynamically allocated
class Instruction
{
    public: 
        std::string PC;
        
        // Instruction info
        unsigned int tag;
        unsigned int op_type;
        
        int src_reg1;
        int src_reg1_val;
        bool src_reg1_ready;
        bool src_reg1_complete;

        int src_reg2;
        int src_reg2_val;
        bool src_reg2_ready;
        bool src_reg2_complete;

        int dest_reg;
        int dest_reg_val;
        bool dest_reg_ready;

        // Stages
        unsigned int IF[2];
        unsigned int ID[2];
        unsigned int IS[2];
        unsigned int EX[2];
        unsigned int WB[2];

        // Current state
        std::string state;

        Instruction (void);
};


std::ostream& operator << (std::ostream &output, Instruction instr);

#endif