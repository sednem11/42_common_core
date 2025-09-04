#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed
{
private:
    int FixedValue;
    static const int    frac;
public:
    Fixed(void);
    ~Fixed(void);
    Fixed(Fixed const &copy);
	Fixed	&operator=(Fixed const &copy);
    int	getRawBits(void) const;
    void	setRawBits(const int raw);
};

#endif