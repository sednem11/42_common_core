#include "Fixed.hpp"

const int   Fixed::frac = 8;

Fixed::Fixed(): FixedValue(0)
{
    std::cout << "Fixed_value set by default constructor" << std::endl;
}

Fixed::~Fixed()
{
    std::cout << "Fixed_value destroyed Default destructor called" << std::endl;
}


Fixed::Fixed(Fixed const & copy)
{
	std::cout << "Fixed object copied" << std::endl;
	*this = copy;
}

Fixed	&Fixed::operator=(const Fixed &copy)
{
	std::cout << "Assignment operator called" << std::endl;
	this->FixedValue = copy.getRawBits();
	return (*this);
}

int	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->FixedValue);
}

void	Fixed::setRawBits(const int raw)
{
	this->FixedValue = raw;
}