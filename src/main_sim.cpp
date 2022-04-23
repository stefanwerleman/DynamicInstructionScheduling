#include <fstream>
#include <iostream>
#include <string>

#include "../libs/ArgumentWrapper/ArgumentWrapper.h"
#include "../libs/Instruction/Instruction.h"

void run_sim(ArgumentWrapper args)
{
    std::fstream file("./data/traces/" + args.trace_file);

    if (!file.is_open())
    {
        std::cout << "FAILED TO OPEN FILE: " << args.trace_file << std::endl;
        return;
    }

    Instruction instr;
    std::string in;

    while (file >> in)
    {
        instr.PC = in;

        file >> in;
        instr.op_type = stoi(in);

        file >> in;
        instr.dest_reg = stoi(in);

        file >> in;
        instr.src_reg1 = stoi(in);

        file >> in;
        instr.src_reg2 = stoi(in);
    }
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