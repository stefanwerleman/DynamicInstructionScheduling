#ifndef FAKE_ROB
#define FAKE_ROB

#include <fstream>
#include <queue>

#include "../ArgumentWrapper/ArgumentWrapper.h"
#include "../Instruction/Instruction.h"

class FakeROB
{
    public:
        std::queue<Instruction*> *fifo;
        std::queue<Instruction*> *dispatch_list;
        std::queue<Instruction*> *issue_list;
        std::queue<Instruction*> *execute_list;

        // Limits
        unsigned int N;
        unsigned int N2;
        unsigned int S;

        // Results
        unsigned int num_instr;
        unsigned int num_cycles;
        double IPC;


        FakeROB (ArgumentWrapper args);
        ~FakeROB (void);
        
        void fake_retire(void);
        void execute(void);
        void issue(void);
        void dispatch(void);
        void fetch(std::fstream *file);
        bool advance_cycle(std::fstream *file);
};

#endif