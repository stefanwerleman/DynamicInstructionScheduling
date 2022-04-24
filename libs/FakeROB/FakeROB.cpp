#include <fstream>
#include <iostream>
#include <queue>
#include <string>

#include "FakeROB.h"

#include "../ArgumentWrapper/ArgumentWrapper.h"
#include "../Instruction/Instruction.h"

FakeROB::FakeROB (ArgumentWrapper args)
{
    this->N = args.N;
    this->N2 = 2 * args.N;
    this->S = args.S;

    this->fifo = new std::queue<Instruction*>;
    this->dispatch_list = new std::queue<Instruction*>;
    this->issue_list = new std::queue<Instruction*>;
    this->execute_list = new std::queue<Instruction*>;
}

FakeROB::~FakeROB (void)
{
    if (this->fifo != NULL)
    {
        while (!this->fifo->empty())
        {
            delete this->fifo->front();
            this->fifo->pop();
        }

        delete this->fifo;
    }


    // * NOTE: No need to free the instructions inside the other lists 
    // * because their references have been handled in the fifo parent queue.
    if (this->dispatch_list != NULL)
    {
        delete this->dispatch_list;
    }

    if (this->issue_list != NULL)
    {
        delete this->issue_list;
    }

    if (this->execute_list != NULL)
    {
        delete this->execute_list;
    }
}

void FakeROB::dispatch(void)
{
    
}

void FakeROB::fetch(std::fstream *file)
{
    unsigned int fetch_count = 0;
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
        if (this->dispatch_list->size() < this->N2)
        {
            instr->state = "ID";
            this->dispatch_list->push(instr);
        }
        
        this->num_instr++;
        if (this->fifo->size() < 1024)
        {
            this->fifo->push(instr);
        }
        
        fetch_count++;
        if (fetch_count >= this->N)
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