#include <fstream>
#include <iostream>
#include <queue>

#include "FakeROB.h"
#include "../Instruction/Instruction.h"

FakeROB::FakeROB (void)
{
    this->fifo = new std::queue<Instruction*>;
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
}

// Returns a bool indicating if there was room to insert the next instr.
bool FakeROB::insert(Instruction *instr)
{
    if (this->fifo->size() < 1)
    {
        this->fifo->push(instr);
        return true;
    }
    else
    {
        return false;
    }
}

bool FakeROB::advance_cycle(std::fstream *file)
{
    // TODO: Need to check if file reader has reached the end of the file.
    if (this->fifo->size() <= 0 && file->peek() == EOF)
        return false;
    else
        return true;
}