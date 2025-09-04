#include "Span.hpp"

Span::Span()
{
    std::cout << "Span Created with default constructor" << std::endl;
}

Span::Span(unsigned int N): _N(N), _pos(0)
{
    std::cout << "Span Created with number limiter of: " << _N << std::endl;
}

Span::Span(const Span &copy): _N(copy._N), _pos(copy._pos)
{
    std::cout << "span copied" << std::endl;
    *this = copy;
}

Span &Span::operator=(const Span &src)
{
    std::cout << "assignment operator called for Span" << std::endl;
    return(*this);
}

Span::~Span()
{
    std::cout << "Destructor called" << std::endl;
}

void Span::addnumber(int number)
{
	if ((this->_pos != 0 && this->_numbers.empty() == true) || this->_numbers.max_size() < this->_N)
		throw (Span::VectorInvalidException());
    if (_pos + 1 > _N)
        throw (ArrayFullException());
    else
    {
        _pos++;
        _numbers.push_back(number);
    }
}

unsigned int Span::shortestSpan() const
{
    if (_pos == 0 || _pos == 1)
        throw(ComparisonInvalidException());
    else{
        std::vector<int> V(this->_numbers);
        std::sort (V.begin(), V.end());
        unsigned int ret = UINT_MAX;
        std::vector<int>::iterator temp_it = V.begin();
        std::vector<int>::iterator temp_it_next = V.begin() + 1;
        while(temp_it_next != V.end())
        {
            if ((unsigned int)(*temp_it_next - *temp_it) < ret)
                ret = *temp_it_next - *temp_it;
            temp_it_next++;
            temp_it++;
        }
        return(ret);
    }
}

unsigned int Span::longestSpan() const
{
    if (_pos == 0 || _pos == 1)
        throw(ComparisonInvalidException());
    else
    {
        std::vector<int> V(this->_numbers);
        std::sort (V.begin(), V.end());
        return(*(V.end() - 1) - *V.begin());
    }
}

const char *Span::VectorInvalidException::what() const throw()
{
    return ("invalide or broken vector\n");
}

const char *Span::ArrayFullException::what() const throw()
{
    return ("Array Full\n");
}

const char *Span::ComparisonInvalidException::what() const throw()
{
    return ("Comparisson error");
}
