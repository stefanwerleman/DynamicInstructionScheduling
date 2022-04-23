#ifndef INSTRUCTION
#define INSTRUCTION

#include <iostream>
#include <string>

const int UNDEFINED = -1e3;

// This is just a carrier for all the traces but will still be dynamically allocated
class Instruction
{
    public: 
        std::string PC = "";             //* NOTE: This is will temporarely be a string. 
        unsigned int op_type = 0;
        int dest_reg = UNDEFINED;
        int src_reg1 = UNDEFINED;
        int src_reg2 = UNDEFINED;
};

#endif