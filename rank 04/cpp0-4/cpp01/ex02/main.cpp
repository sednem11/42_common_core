#include <iostream>

int main(void)
{
    std::string string;
    std::string *strpointer;

    string = "HI THIS IS BRAIN";
    strpointer = &string;
    std::string &stringREF = string;
    std::cout << "string address: " << &string << std::endl;
    std::cout << "string pointer address: " << strpointer << std::endl;
    std::cout << "string reference address: " << &stringREF << std::endl;
    std::cout << "string pointer string: " << *strpointer << std::endl;
    std::cout << "string reference string: " << stringREF << std::endl;
}