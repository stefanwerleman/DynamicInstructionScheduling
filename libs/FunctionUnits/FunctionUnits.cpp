#include <queue>

#include "FunctionUnits.h"
#include "../Instruction/Instruction.h"

FunctionUnits::FunctionUnits (void)
{
    this->execute_list = new std::queue<Instruction*>;
}

FunctionUnits::~FunctionUnits (void)
{
    if (this->execute_list != NULL)
    {
        Instruction *temp;
        for (int i = 0; !this->execute_list->empty() ; i++)
        {
            temp = this->execute_list->front();
            this->execute_list->pop();
            
            if (temp != NULL)
            {
                delete temp;
            }
        }

        delete this->execute_list;
    }
}