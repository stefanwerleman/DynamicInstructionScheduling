#ifndef SCHEDULING_QUEUE
#define SCHEDULING_QUEUE

#include <queue>

#include "../Instruction/Instruction.h"

class SchedulingQueue
{
    public:
        std::queue<Instruction*> *issue_list;

        SchedulingQueue (void);
        ~SchedulingQueue (void);
};

#endif