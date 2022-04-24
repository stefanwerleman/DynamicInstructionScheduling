#ifndef FAKE_ROB
#define FAKE_ROB

#include <fstream>
#include <queue>

#include "../DispatchQueue/DispatchQueue.h"
#include "../FunctionUnits/FunctionUnits.h"
#include "../Instruction/Instruction.h"
#include "../SchedulingQueue/SchedulingQueue.h"

class FakeROB
{
    public:
        DispatchQueue *dq;
        SchedulingQueue *sq;
        FunctionUnits *fu;

        std::queue<Instruction*> *fifo;

        // Results
        unsigned int num_instr;
        unsigned int num_cycles;
        double IPC;


        FakeROB (void);
        ~FakeROB (void);
        
        bool insert(Instruction *instr);
        void fetch(std::fstream *file);
        bool advance_cycle(std::fstream *file);
};

#endif