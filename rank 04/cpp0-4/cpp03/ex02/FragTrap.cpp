#include "FragTrap.hpp"

FragTrap::FragTrap(void): ClapTrap("default")
{
	this->_Hpoints = 100;
	this->_Epoints = 50;
	this->_Adamage = 20;
}

FragTrap::FragTrap(std::string const &name): ClapTrap(name)
{
	std::cout << "FragTrap from ClapTrap " << this->_name << " created." << std::endl;
	this->_Hpoints = 100;
	this->_Epoints = 100;
	this->_Adamage = 30;
}

FragTrap::~FragTrap(void)
{
	std::cout << "FragTrap from ClapTrap " << this->_name << " destroyed." << std::endl;
	this->_Hpoints = 100;
	this->_Epoints = 100;
	this->_Adamage = 30;
}

FragTrap::FragTrap(FragTrap const &copy): ClapTrap(copy)
{
    *this = copy;
}

FragTrap &FragTrap::operator=(FragTrap const &copy)
{
    this->_Adamage = copy._Adamage;
    this->_Epoints = copy._Epoints;
    this->_Hpoints = copy._Hpoints;
	return(*this);
}

void	FragTrap::HighFivesGuys(void)
{
	if (this->_Hpoints <= 0)
		std::cout << "Cannot high five because: ClapTrap " << this->_name << " is dead." << std::endl;
	else
		std::cout << "FragTrap from ClapTrap " << this->_name << " says: \"HIGH FIVE EVERYONE! :)\"." << std::endl;
}