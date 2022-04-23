#include <iostream>

#include "ArgumentWrapper.h"

ArgumentWrapper::ArgumentWrapper (int argc, char **argv)
{
    this->S = atoi(argv[1]);
    this->N = atoi(argv[2]);
    this->trace_file = argv[3];
}

std::ostream& operator << (std::ostream &output, ArgumentWrapper arguments)
{
    output << "./sim ";
    output << arguments.S << " ";
    output << arguments.N << " ";
    output << arguments.trace_file << " ";

    return output;
}
