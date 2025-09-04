#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap: public ClapTrap
{
    public:
    FragTrap(void);
    FragTrap(std::string const &name);
    ~FragTrap(void);
    FragTrap(FragTrap const &copy);
    FragTrap    &operator=(FragTrap const &copy);
    void    HighFivesGuys(void);
};

#endif