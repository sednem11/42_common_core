#include "Zombie.hpp"

Zombie::Zombie (void)
{
    this->name = "(null)";
    std::cout << "Zombie " << this->name << " created" << std::endl;
}

Zombie::Zombie(std::string name)
{
    this->name = name;
    std::cout << " Zombie" << this->name << " created" << std::endl;
}

Zombie::~Zombie()
{
    std::cout << "Zombie " << this->name << " destroyed" << std::endl;
}

void    Zombie::announce(void)
{
    std::cout << this->name << " BraiiiiiiinnnzzzZ..." << std::endl;
}

void    Zombie::setname(std::string name)
{
    this->name = name;
}