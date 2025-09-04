#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>

class ClapTrap
{
    protected:
        std::string _name;
        int         _Hpoints;
        int         _Epoints;
        int         _Adamage;
    public:
        ClapTrap(void);
        ClapTrap(std::string name);
        ~ClapTrap();
        ClapTrap(ClapTrap const &copy);
        ClapTrap    &operator=(ClapTrap const &copy);
        void    attack(const std::string& target);
        void    takeDamage(unsigned int amount);
        void    beRepaired(unsigned int amount);
        int     get_Health(void);
};

#endif