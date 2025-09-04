#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream>

class Weapon
{
    private:
        std::string type;
    public:
        Weapon(std::string type);
        ~Weapon(void);
        const   std::string&  get_type(void);
        void    set_type(std::string type);
};

# endif