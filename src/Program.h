#pragma once

#include "VirtualMachine.h"
#include <Compiler.h>
#include <argparse/argparse.hpp>

namespace zinc {
class Program {
public:
    Program(int argc, char **argv);

    // run the program and return the code returned by VM or error caused by
    // compilation
    int run();

private:
    // program name to compile and execute
    std::string m_progName;

    lang::Compiler m_compiler;
    vm::VirtualMachine m_vm;
};
}