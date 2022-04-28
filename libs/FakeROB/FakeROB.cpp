#include <deque>
#include <fstream>
#include <iostream>
#include <string>

#include "FakeROB.h"

#include "../ArgumentWrapper/ArgumentWrapper.h"
#include "../Instruction/Instruction.h"

const unsigned int REGISTER_SIZE = 128;

FakeROB::FakeROB (ArgumentWrapper args)
{
    this->N = args.N;
    this->N2 = 2 * args.N;
    this->S = args.S;

    this->fifo = new std::deque<Instruction*>;
    this->dispatch_list = new std::deque<Instruction*>;
    this->issue_list = new std::deque<Instruction*>;
    this->execute_list = new std::deque<Instruction*>;
    this->temp_list = new std::deque<Instruction*>;
    this->ready_list = new std::deque<Instruction*>;

    this->register_file = new Register[REGISTER_SIZE];

    for (int i = 0; i < REGISTER_SIZE; i++)
        this->register_file[i].tag = i;
}

FakeROB::~FakeROB (void)
{
    if (this->fifo != NULL)
    {
        while (!this->fifo->empty())
        {
            delete this->fifo->front();
            this->fifo->pop_front();
        }

        delete this->fifo;
    }


    // * NOTE: No need to free the instructions inside the other lists 
    // * because their references have been handled in the fifo parent queue.
    if (this->dispatch_list != NULL)
        delete this->dispatch_list;

    if (this->issue_list != NULL)
        delete this->issue_list;

    if (this->execute_list != NULL)
        delete this->execute_list;

    if (this->temp_list != NULL)
        delete this->temp_list;

    if (this->ready_list != NULL)
        delete this->ready_list;

    if (this->register_file != NULL)
        delete [] this->register_file;
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

        this->fifo->pop_front();
    }
}

void FakeROB::execute(void)
{
    while (!this->execute_list->empty())
    {
        this->execute_list->front()->state = "WB";
        this->execute_list->pop_front();
    }
}

void FakeROB::issue(void)
{
    Instruction *instr;
    int size = this->issue_list->size();

    for (int i = 0; i < size; i++)
    {
        instr = this->issue_list->front();
        this->issue_list->pop_front();
        
        if (instr->src_reg1_ready && instr->src_reg2_ready)
        {
            this->ready_list->push_back(instr);
        }
        else
        {
            this->issue_list->push_back(instr);
        }
    }

    // TODO: Add all ready instructions to temp_list[].
    // * NOTE: temp_list[] will act as a ready_list[]. 
    // *       Or it might be better to create a separate one     
    while (!this->ready_list->empty())
    {
        std::cout << "===================INSERT===================" << std::endl;
        this->ready_list->front()->state = "EX";
        this->execute_list->push_back(this->ready_list->front());

        this->ready_list->pop_front();
    }
}

void FakeROB::rename(Instruction *instr)
{
    if (instr->src_reg1 != -1 && this->register_file[instr->src_reg1].ready)
    {
        instr->src_reg1_ready = this->register_file[instr->src_reg1].ready;
        instr->src_reg1_val = this->register_file[instr->src_reg1].tag;
    }

    if (instr->src_reg2 != -1 && this->register_file[instr->src_reg2].ready)
    {
        instr->src_reg2_ready = this->register_file[instr->src_reg2].ready;
        instr->src_reg2_val = this->register_file[instr->src_reg2].tag;
    }

    // TODO: Go back to this one if it acts up.
    if (instr->dest_reg != -1)
    {
        // * register_file == RAT
        this->register_file[instr->dest_reg].ready = false;
        this->register_file[instr->dest_reg].tag = instr->tag;
    }
}

void FakeROB::dispatch(void)
{
    while (!this->dispatch_list->empty() && this->dispatch_list->front()->state == "ID")
    {
        this->temp_list->push_back(this->dispatch_list->front());
        this->dispatch_list->pop_front();
    }

    while (!this->temp_list->empty() && this->issue_list->size() < this->S)
    {
        this->temp_list->front()->state = "IS";
        this->rename(this->temp_list->front());

        this->issue_list->push_back(this->temp_list->front());
        this->temp_list->pop_front();
    }

    for (int i = 0; i < this->dispatch_list->size(); i++)
        this->dispatch_list->at(i)->state = "ID";
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
        
        // ROB
        this->fifo->push_back(instr);
        this->dispatch_list->push_back(instr);

        this->num_instr++;
    }
}

bool FakeROB::advance_cycle(std::fstream *file)
{
    // ROB
    if (this->fifo->size() <= 0 && file->peek() == EOF)
        return false;
    else
        return true;
}