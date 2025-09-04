#include "Span.hpp"

int main(void)
{
    Span a = Span(5);
    a.addnumber(10);
    try{
        std::cout << a.longestSpan() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    a.addnumber(20);
    a.addnumber(15);
    try{
        std::cout << "long span: " << a.longestSpan() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    try{
        std::cout << "short span: " << a.shortestSpan() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    try
    {
            a.addnumber(40);
            a.addnumber(1);
            a.addnumber(55);
    }
    catch(std::exception &e)
    {
        std::cerr << e.what();
    }
    try{
        std::cout << "long span: " << a.longestSpan() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    try{
        std::cout << "short span: " << a.shortestSpan() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}