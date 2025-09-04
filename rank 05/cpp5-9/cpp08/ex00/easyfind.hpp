#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>

class NotFoundException: public std::exception
{
    public:
        virtual const char *what() const throw()
        {
            return("Not found");
        }
};

template<typename T>
typename T::iterator easyfind(T &temp, int n)
{
    typename T::iterator    it;
    it = find(temp.begin(), temp.end(), n);
    if (it == temp.end())
    {
        std::cerr << n << " ";
        throw(NotFoundException());
    }
    return(it);
}
