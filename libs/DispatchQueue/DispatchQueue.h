#ifndef DISPATCH_QUEUE
#define DISPATCH_QUEUE

#include <queue>

#include "../Instruction/Instruction.h"

class DispatchQueue
{
    public:
        std::queue<Instruction*> *dispatch_list;        

        DispatchQueue (void);
        ~DispatchQueue (void);
};

#endif