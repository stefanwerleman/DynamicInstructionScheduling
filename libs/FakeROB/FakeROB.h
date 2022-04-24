#ifndef FAKEROB
#define FAKEROB

#include <queue>
#include "../Instruction/Instruction.h"

class FakeROB
{
    public:
        std::queue<Instruction*> *fifo;

        // Results
        unsigned int num_instr;
        unsigned int num_cycles;
        double IPC;

        FakeROB (void);
        ~FakeROB (void);
        
        bool insert(Instruction *instr);
        bool advance_cycle(std::fstream *file);
};

#endif