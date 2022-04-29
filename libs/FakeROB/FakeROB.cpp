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
        this->fifo->front()->WB[0] = this->fifo->front()->EX[0] + this->fifo->front()->EX[1];
        this->fifo->front()->WB[1] = 1;
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
    for (int i = 0; i < this->execute_list->size(); i++)
    {
        this->execute_list->front()->EX[0] = this->execute_list->front()->IS[0] + this->execute_list->front()->IS[1];
        if ((this->execute_list->front()->op_type == 0 && this->execute_list->front()->EX[1] == 1) || (this->execute_list->front()->op_type == 1 && this->execute_list->front()->EX[1] == 2) || (this->execute_list->front()->op_type == 2 && this->execute_list->front()->EX[1] == 5))
        {
            this->execute_list->front()->state = "WB";

            if (this->execute_list->front()->dest_reg != -1)
            {
                this->register_file[this->execute_list->front()->dest_reg].tag = -1;
            }

            this->execute_list->pop_front();
        }
        else
        {
            this->execute_list->front()->EX[1]++;
        }
    }

    for (int i = 0; i < this->issue_list->size(); i++)
    {
        if (!this->issue_list->at(i)->src_reg1_ready && this->register_file[this->issue_list->at(i)->src_reg1].tag == -1)
        {
            this->issue_list->at(i)->src_reg1_ready = true;
        }

        if (!this->issue_list->at(i)->src_reg2_ready && this->register_file[this->issue_list->at(i)->src_reg2].tag == -1)
        {
            this->issue_list->at(i)->src_reg2_ready = true;
        }
    }
}

void FakeROB::issue(void)
{
    Instruction *instr;

    for (int i = 0; i < this->issue_list->size(); i++)
    {
        this->issue_list->at(i)->IS[1]++;
    }

    for (int i = 0; i < this->issue_list->size(); i++)
    {
        instr = this->issue_list->front(); 
        instr->IS[0] = instr->ID[0] + instr->ID[1];
        this->issue_list->pop_front();
        if (instr->state == "IS" && instr->src_reg1_ready && instr->src_reg2_ready)
        {
            instr->state = "EX";
            this->execute_list->push_back(instr);
        }
        else
        {
            this->issue_list->push_back(instr);
        }
    }

}

void FakeROB::rename(Instruction *instr)
{
    if (instr->src_reg1 != -1 && this->register_file[instr->src_reg1].ready)
    {
        instr->src_reg1_ready = this->register_file[instr->src_reg1].ready;
        instr->src_reg1_val = this->register_file[instr->src_reg1].tag;
    }
    else
    {
        instr->src_reg1_val = -1;
        instr->src_reg1_ready = true;
    }

    if (instr->src_reg2 != -1 && this->register_file[instr->src_reg2].ready)
    {
        instr->src_reg2_ready = this->register_file[instr->src_reg2].ready;
        instr->src_reg2_val = this->register_file[instr->src_reg2].tag;
    }
    else
    {
        instr->src_reg2_val = -1;
        instr->src_reg2_ready = true;
    }

    if (instr->dest_reg != -1)
    {
        this->register_file[instr->dest_reg].ready = false;
        this->register_file[instr->dest_reg].tag = instr->tag;
    }
    else
    {
        instr->dest_reg_ready = true;
        instr->dest_reg_val = -1;
    }
}

void FakeROB::dispatch(void)
{
    while (!this->dispatch_list->empty() && this->dispatch_list->front()->state == "ID")
    {
        this->dispatch_list->front()->ID[0] = this->dispatch_list->front()->IF[0] + this->dispatch_list->front()->IF[1];
        this->temp_list->push_back(this->dispatch_list->front());
        this->dispatch_list->pop_front();
    }

    for (int i = 0; i < this->temp_list->size(); i++)
    {
        this->temp_list->at(i)->ID[1]++;
    }
    
    for (int i = 0; i < this->temp_list->size(); i++)
    {
        if (this->issue_list->size() < this->S)
        {
            this->temp_list->front()->state = "IS";
            this->rename(this->temp_list->front());
            this->issue_list->push_back(this->temp_list->front());
            this->temp_list->pop_front();
        }
    }

    // Unconditionally set instructions in IF to ID state.
    for (int i = 0; i < this->dispatch_list->size(); i++)
    {
        this->dispatch_list->at(i)->state = "ID";
        this->dispatch_list->at(i)->IF[1] = 1;
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
        instr->IF[0] = this->num_cycles;
        
        // ROB
        this->fifo->push_back(instr);
        this->dispatch_list->push_back(instr);

        fetch_count++;
        this->num_instr++;
    }
    // std::cout << "num_fetched: " << this->num_instr << std::endl;
}

bool FakeROB::advance_cycle(std::fstream *file)
{
    // ROB
    if (this->fifo->size() <= 0 && file->peek() == EOF)
        return false;
    else
        return true;
}