#include "iter.hpp"
#include <iostream>
#include <cctype>

void    subtract1(char &arr)
{
    arr -= 1;
}

int main(void)
{
    std::string array1 = "bcde";

    ::Iter(&array1[0], 4, subtract1);
    std::cout << array1 << std::endl;
}