#ifndef ARGUMENT_WRAPPER
#define ARGUMENT_WRAPPER

#include <iostream>
#include <string>

class ArgumentWrapper
{
    public:
        unsigned int S;
        unsigned int N;
        std::string trace_file;

        ArgumentWrapper(int argc, char **argv);
};

#endif