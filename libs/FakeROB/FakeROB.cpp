#include <fstream>
#include <iostream>
#include <queue>
#include <string>

#include "FakeROB.h"

#include "../DispatchQueue/DispatchQueue.h"
#include "../Instruction/Instruction.h"
#include "../SchedulingQueue/SchedulingQueue.h"

FakeROB::FakeROB (void)
{
    this->fifo = new std::queue<Instruction*>;

    this->dq = new DispatchQueue();
    this->sq = new SchedulingQueue();
}

FakeROB::~FakeROB (void)
{
    if (this->fifo != NULL)
    {
        Instruction *temp;
        for (int i = 0; !this->fifo->empty() ; i++)
        {
            temp = this->fifo->front();
            this->fifo->pop();
            
            if (temp != NULL)
            {
                delete temp;
            }
        }

        delete this->fifo;
    }

    if (this->dq != NULL)
    {
        delete this->dq;
    }

    if (this->sq != NULL)
    {
        delete this->sq;
    }
}

// Returns a bool indicating if there was room to insert the next instr.
bool FakeROB::insert(Instruction *instr)
{
    if (this->fifo->size() < 1024)
    {
        this->fifo->push(instr);
        return true;
    }
    else
    {
        return false;
    }
}

void FakeROB::fetch(std::fstream *file)
{
    std::string in;
    while ((*file) >> in)
    {
        Instruction *instr = new Instruction();

        instr->PC = in;

        (*file) >> in;
        instr->op_type = stoi(in);

        (*file) >> in;
        instr->dest_reg = stoi(in);

        (*file) >> in;
        instr->src_reg1 = stoi(in);

        (*file) >> in;
        instr->src_reg2 = stoi(in);

        instr->tag = this->num_instr;

        // TODO: If inserted to dispatch_list DispatchQueue, set state to ID unconditionally.
        
        this->num_instr++;

        if (!this->insert(instr))
        {
            return;
        }
    }
}

bool FakeROB::advance_cycle(std::fstream *file)
{
    if (this->fifo->size() <= 0 && file->peek() == EOF)
        return false;
    else
        return true;
}