#include "HumanB.hpp"

HumanB::HumanB(std::string name): weapon(NULL)
{
    this->name = name;
    std::cout << "HumanB " << name << " created with no weapon" << std::endl;
}

HumanB::~HumanB(void)
{
    std::cout << "HumanB " << this->name << " destroyed" << std::endl;
}

void    HumanB::attack(void)
{
    if (!this->weapon)
        std::cout << this->name << " attacks with is head because he forgot the pistol at home" << std::endl;
    else
	    std::cout << this->name << " attacks with his " << this->weapon->get_type() << std::endl;
}

void    HumanB::set_weapon(Weapon *weapon)
{
    this->weapon = weapon;
}