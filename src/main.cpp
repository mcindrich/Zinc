#include <Zinc.hpp>
using namespace zinc;

int main(int argc, char **argv)
{
    lang::Parser parser;
    parser.parseFile(argv[1]);
    return 0;
}