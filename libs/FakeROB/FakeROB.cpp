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

void FakeROB::fake_retire(void)
{
    Instruction *instr = NULL;
    while (!this->fifo->empty() && this->fifo->front()->state == "WB")
    {
        std::cout << *(this->fifo->front());
        if (this->fifo->front() != NULL)
        {
            delete this->fifo->front();;
        }

        this->fifo->pop();
    }
}

void FakeROB::execute(void)
{
    while (!this->execute_list->empty())
    {
        this->execute_list->front()->state = "WB";
        this->execute_list->pop();
    }
}

void FakeROB::issue(void)
{
    while (!this->issue_list->empty())
    {
        this->issue_list->front()->state = "EX";
        this->execute_list->push(this->issue_list->front());
        this->issue_list->pop();
    }
}

void FakeROB::dispatch(void)
{
    while (this->issue_list->size() < this->S && !this->dispatch_list->empty())
    {
        this->dispatch_list->front()->state = "IS";
        this->issue_list->push(this->dispatch_list->front());
        this->dispatch_list->pop();
    }
}

void FakeROB::fetch(std::fstream *file)
{
    unsigned int fetch_count = 0;
    std::string in;
    Instruction *instr = NULL;

    while (fetch_count < this->N && this->dispatch_list->size() < this->N2)
    {   
        (*file) >> in;
        
        if (file->eof())
        {
            return;
        }

        instr = new Instruction();
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
        this->fifo->push(instr);
        this->dispatch_list->push(instr);

        this->num_instr++;
    }
}

bool FakeROB::advance_cycle(std::fstream *file)
{
    if (this->fifo->size() <= 0 && file->peek() == EOF)
        return false;
    else
        return true;
}