#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <time.h>
#include <iomanip>

class PmergeMe
{
private:
    std::vector<int>stack1;
    std::deque<int>stack2;
public:
    PmergeMe();
    ~PmergeMe();

    PmergeMe(const PmergeMe &copy);
    PmergeMe &operator=(const PmergeMe &copy);
    int     set_arguments(char *arg);
    void    sorting_process();
    void    sort_vector();
    void    sort_deque();
    void    output(char **arguments);
};
