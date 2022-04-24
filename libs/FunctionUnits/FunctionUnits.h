#ifndef FUNCTION_UNITS
#define FUNCTION_UNITS

#include <queue>

#include "../Instruction/Instruction.h"

class FunctionUnits
{
    public:
        std::queue<Instruction*> *execute_list;

        FunctionUnits (void);
        ~FunctionUnits (void);
};

#endif