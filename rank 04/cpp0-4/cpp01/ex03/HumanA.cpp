#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon): name(name), weapon(weapon)
{
	std::cout << "HumanA " << name << " created with " << weapon.get_type() << std::endl;
}

HumanA::~HumanA(void)
{
    std::cout << "HumanA " << this->name << " destroyed" << std::endl;
}

void    HumanA::attack(void)
{
	std::cout << this->name << " attacks with his " << this->weapon.get_type() << std::endl;
}

void    HumanA::set_weapon(Weapon weapon)
{
    this->weapon = weapon;
}