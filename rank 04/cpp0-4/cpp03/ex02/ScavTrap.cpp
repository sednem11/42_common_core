#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void): ClapTrap("default")
{
	this->_Hpoints = 100;
	this->_Epoints = 50;
	this->_Adamage = 20;
}

ScavTrap::ScavTrap(std::string const &name): ClapTrap(name)
{
	std::cout << "ScavTrap from ClapTrap " << this->_name << " created." << std::endl;
	this->_Hpoints = 100;
	this->_Epoints = 50;
	this->_Adamage = 20;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "ScavTrap from ClapTrap " << this->_name << " destroyed." << std::endl;
	this->_Hpoints = 100;
	this->_Epoints = 50;
	this->_Adamage = 20;
}

ScavTrap::ScavTrap(ScavTrap const &copy): ClapTrap(copy._name)
{
    *this = copy;
}

ScavTrap &ScavTrap::operator=(ScavTrap const &copy)
{
    this->_Adamage = copy._Adamage;
    this->_Epoints = copy._Epoints;
    this->_Hpoints = copy._Hpoints;
	return(*this);
}


void	ScavTrap::GuardGate()
{
	if (this->_Hpoints <= 0)
		std::cout << "Cannot switch to gate-keeper mode because: ClapTrap " << this->_name << " is dead." << std::endl;
	else
		std::cout << "ScavTrap from ClapTrap " << this->_name << " switched to mode: \"Guard Gate\"." << std::endl;
}
