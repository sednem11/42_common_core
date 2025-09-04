#pragma once

#include <iostream>
#include <sstream>
#include <stack>

class RPN
{
private:
    std::stack<int> stack;
    void    plus(int first, int second);
    void    minus(int first, int second);
    void    multiply(int first, int second);
    void    divide(int first, int second);
public:
    RPN();
    ~RPN();

    RPN &operator=(const RPN &copy);
    RPN (const RPN &copy);
    void    set_arguments(std::string argument);
    void     reverse_PN();
    void     reverse_PN2();
};
