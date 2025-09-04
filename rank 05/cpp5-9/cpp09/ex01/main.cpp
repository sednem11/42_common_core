#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: needes 1 argument" << std::endl;
        return -1;
    }
    RPN rpn = RPN();
    rpn.set_arguments(argv[1]);
}