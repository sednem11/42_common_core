#pragma once

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <climits>

class Span
{
    private:
        std::vector<int> _numbers;
        unsigned int _N;
        unsigned int _pos;
        Span();
    public:
        Span(unsigned int N);
        Span(const Span &copy);

        Span &operator=(const Span &src);

        ~Span();
        void addnumber(int number);
		unsigned int shortestSpan()const;
		unsigned int longestSpan()const;

	class	VectorInvalidException : public std::exception
	{
		public:
			virtual const char	*what() const throw();
	};

	class	ArrayFullException : public std::exception
	{
		public:
			virtual const char	*what() const throw();
	};

	class	ComparisonInvalidException : public std::exception
	{
		public:
			virtual const char	*what() const throw();
	};
};
