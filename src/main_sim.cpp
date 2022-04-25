#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

#include "../libs/ArgumentWrapper/ArgumentWrapper.h"
#include "../libs/Instruction/Instruction.h"
#include "../libs/FakeROB/FakeROB.h"

void run_sim(ArgumentWrapper args)
{
    std::fstream file("./data/traces/" + args.trace_file);

    if (!file.is_open())
    {
        std::cout << "FAILED TO OPEN FILE: " << args.trace_file << std::endl;
        return;
    }

    FakeROB *fr = new FakeROB(args);

    do
    {
        fr->fake_retire();
        fr->execute();
        fr->issue();
        fr->dispatch();
        fr->fetch(&file);
        fr->num_cycles++;
    }
    while (fr->advance_cycle(&file));

    fr->IPC = (double)fr->num_instr / fr->num_cycles;

    /**
     * ! This entire loop is FakeROB
     * 
     * * Start of a Cycle
     *      * FakeRetire():
     *      ? 1. Remove instructions from the head of the FIFO until 
     *      ?    you reached an instruction that is not in the WB state.
     *      ?    (i.e. remove all WB instructions from FIFO)
     *      ! If nothing is in the FIFO, do nothing.
     * 
     *      * Execute():
     *      ? 1. On the instruction that is done executing in this cycle:
     *      ?    A. Remove instruction from execute_list[].
     *      ?    B. Transition from EX state to WB state. Set the state of the instructionto WB
     *      ?    C. Update the register file state and wakeup dependent instructions.
     *      ! If nothing is in the execute_list[], do nothing     
     * 
     *      * Issue():
     *      ? 1. Scan the ready instructions in the ready_list in 
     *      ?    the order of tags and issue up to N+1 of them. 
     *      ? 2. ISSUE:
     *      ?    A. Remove the instruction from the issue_list[]
     *      ?    B. Add the instruction to the execute_list[]
     *      ?    C. Transition from the IS state to the EX state. Set the state of the instruction to EX
     *      ?    D. Free up the scheduling queue entry 
     *      ?       (decrement a count of the number of instructions in the scheduling queue)
     *      ?    E. Set a timer in the instruction's data structure that 
     *      ?       will allow you to model the execution latency.
     *      ! If nothing is in the ready_list[] and issue_list[], do nothing.
     * 
     *      * Dispatch():
     *      ? 1. If the SchedulingQueue (issue_list[]) is not full, then:
     *      ?    A. Remove the instruction from the dispatch_list[] and add it to the issue_list[]
     *      ?    B. Transition from the ID state to the IS state. Set the state of the instruction to IS
     *      ?    C. Rename source operands by looking up the state in the RegisterFile
     *      ! If nothing is in the dispatch_list[], do nothing.
     *      
     *      * Fetch():
     *      ? 2. Read new instructions from the trace until the fetch bandwidth is full or DispatchQueue is full.
     *      ?    A. Push new instruction to FIFO.
     *      ?    B. Set its state to IF.
     *      ?    C. Add instruction to the dispatch_list[] and reserve a DispatchQueue entry. 
     *      ?       For instructions in the dispatch_list[] set the state of instructions to ID.
     * * End of a Cycle
     * * AdvanceCycle():
     * ? 1. If the FIFO is empty AND the trace is depleted, return False to the terminate the loop.
     * ? 2. Otherwise, advance the simulator cycle.
    */

    std::cout << "number of instructions = " << fr->num_instr << std::endl;
    std::cout << "number of cycles =       " << fr->num_cycles << std::endl;

    std::cout << std::fixed;
    std::cout << "IPC =                    " <<  std::setprecision(5) <<  fr->IPC << std::endl;

    delete fr;
    file.close();
}

int main(int argc, char **argv)
{
    if (argc < 4 || argc > 4)
    {
        std::cout << "MISSING COMMAND LINE ARGUMENTS" << std::endl;
        return 1;
    }

    // This is static because it is only used once throughout the entire program.
    ArgumentWrapper arguments(argc, argv);
    run_sim(arguments);

    return 0;
}