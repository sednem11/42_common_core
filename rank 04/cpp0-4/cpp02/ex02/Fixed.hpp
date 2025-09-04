#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
private:
    int _value;
    static const int _frac;
public:
    Fixed(const int value);
    Fixed(const float value);
    Fixed(void);
    ~Fixed();
    Fixed(Fixed const &copy);

	Fixed	&operator=(Fixed const &copy);
	Fixed	operator+(Fixed const &copy) const;
    Fixed	operator-(Fixed const &copy) const;
    Fixed	operator*(Fixed const &copy) const;
    Fixed	operator/(Fixed const &copy) const;
    bool	operator==(Fixed const &copy) const;
    bool	operator!=(Fixed const &copy) const;
    bool	operator<=(Fixed const &copy) const;
    bool	operator>=(Fixed const &copy) const;
    bool	operator<(Fixed const &copy) const;
    bool	operator>(Fixed const &copy) const;

    Fixed	&operator++(void);
    Fixed	&operator--(void);
    Fixed	operator++(int value);
    Fixed	operator--(int value);

    static const Fixed	&min(Fixed const &copy1, Fixed const &copy2);
    static const Fixed	&max(Fixed const &copy1, Fixed const &copy2);
    static Fixed	&min(Fixed &copy1, Fixed &copy2);
    static Fixed	&max(Fixed &copy1, Fixed &copy2);  

    float   toFloat(void) const;
    int     toInt(void) const;
    int		getRawBits(void) const;
    void	setRawBits(int const raw);
};

std::ostream	&operator<<(std::ostream &str, Fixed const &fixed_nbr);

#endif