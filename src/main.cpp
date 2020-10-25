#include <Zinc.hpp>
#include <argparse/argparse.hpp>

int main(int argc, char **argv)
{
    zinc::Program prog(argc, argv);

    return prog.run();
}