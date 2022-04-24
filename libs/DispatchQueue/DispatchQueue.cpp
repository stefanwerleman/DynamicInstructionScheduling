#include <queue>

#include "DispatchQueue.h"
#include "../Instruction/Instruction.h"

DispatchQueue::DispatchQueue (void)
{
    this->dispatch_list = new std::queue<Instruction*>;
}

DispatchQueue::~DispatchQueue (void)
{
    if (this->dispatch_list != NULL)
    {
        Instruction *temp;
        for (int i = 0; !this->dispatch_list->empty() ; i++)
        {
            temp = this->dispatch_list->front();
            this->dispatch_list->pop();
            
            if (temp != NULL)
            {
                delete temp;
            }
        }

        delete this->dispatch_list;
    }
}