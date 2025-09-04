#pragma once

#include <iostream>
#include <stack>

template <class T>
class MutantStack: public std::stack<T>
{
public:
    typedef std::stack<T> stack;
    typedef typename stack::container_type container;
    typedef typename container::iterator iterator;

    MutantStack(): stack()
    {
        std::cout << "Default contructor called for MutatedStack" << std::endl;
    }

    MutantStack(const stack &copy): stack(copy)
    {
        std::cout << "MutatedStack copied" << std::endl;
        *this = copy;
    }

    MutantStack &operator=(const MutantStack &copy)
    {
        std::cout << "Asignment operator called for MutatedStack" << std::endl;
        if (this != &copy)
            std::stack<T>::operator=(copy);
        return(*this);
    }

    ~MutantStack()
    {
        std::cout << "MutatedStack destroyed" << std::endl;
    }

	iterator begin()
	{
		return (stack::c.begin());
	}

	iterator end()
	{
		return (stack::c.end());
	}
};
