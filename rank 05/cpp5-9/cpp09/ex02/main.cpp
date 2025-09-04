#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        std::cerr << "No Arguments Stated" << std::endl;
        return (-1);
    }
    PmergeMe V = PmergeMe();
    for (int i = 1; argv[i] != NULL; i++)
    {
        if (V.set_arguments(argv[i]) == -1)
            return (-1);
    }
    V.sorting_process();
    V.output(argv);
}