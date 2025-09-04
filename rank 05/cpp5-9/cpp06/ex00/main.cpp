#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "One argument needed for conversion" << std::endl;
        return(1);
    }
    try
    {
        ScalarConverter ScalarConverter(argv[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return(0);
}