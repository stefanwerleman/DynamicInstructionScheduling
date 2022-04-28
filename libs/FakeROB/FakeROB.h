#ifndef FAKE_ROB
#define FAKE_ROB

#include <deque>
#include <fstream>

#include "../ArgumentWrapper/ArgumentWrapper.h"
#include "../Instruction/Instruction.h"
#include "../Register/Register.h"

class FakeROB
{
    public:
        // ROB
        std::deque<Instruction*> *fifo;
        
        std::deque<Instruction*> *dispatch_list;
        std::deque<Instruction*> *issue_list;
        std::deque<Instruction*> *execute_list;

        std::deque<Instruction*> *temp_list;
        std::deque<Instruction*> *ready_list;

        Register *register_file;

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

        void rename(Instruction *instr);
        void dispatch(void);
        
        void fetch(std::fstream *file);
        bool advance_cycle(std::fstream *file);
};

#endif