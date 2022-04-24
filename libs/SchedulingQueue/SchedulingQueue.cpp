#include <queue>

#include "SchedulingQueue.h"
#include "../Instruction/Instruction.h"

SchedulingQueue::SchedulingQueue (void)
{
    this->issue_list = new std::queue<Instruction*>;
}

SchedulingQueue::~SchedulingQueue (void)
{
    if (this->issue_list != NULL)
    {
        Instruction *temp;
        for (int i = 0; !this->issue_list->empty() ; i++)
        {
            temp = this->issue_list->front();
            this->issue_list->pop();
            
            if (temp != NULL)
            {
                delete temp;
            }
        }

        delete this->issue_list;
    }
}
