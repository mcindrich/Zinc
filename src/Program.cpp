#include <Program.h>
#include <pattern/PatternNotFoundException.h>

namespace zinc {
Program::Program(int argc, char **argv)
{
    argparse::ArgumentParser argp("zinc");
    argp.add_argument("fname")
        .help("file name of a program to run")
        .action([](const std::string &value) { return value; });

    try {
        argp.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
        std::cout << argp;
        exit(0);
    }

    m_progName = argp.get<std::string>("fname");
}

int Program::run()
{
    int ret = 0;
    try {
        m_compiler.compile(m_progName);
        ret = m_vm.execute(m_compiler.getInstructions());
    } catch (lang::PatternNotFoundException &ex) {
        std::cerr << "Pattern and parsing exception: " << std::endl;
        std::cerr << ex.what() << std::endl;
    } catch (std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
}