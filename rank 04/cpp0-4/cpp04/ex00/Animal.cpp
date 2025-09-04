#include "Animal.hpp"

Animal::Animal(): _type("undefined")
{
    std::cout << "Animal type " << this->getType() << " Created" << std::endl << std::endl;
}

Animal::Animal(std::string const &type): _type(type)
{
    std::cout << "Animal type " << this->getType() << " Created" << std::endl << std::endl;
}

Animal::Animal(Animal const &copy)
{
	*this = copy;
	std::cout << "Animal " << this->_type << " copied." << std::endl;
}

Animal const	&Animal::operator=(Animal const &copy)
{
	this->_type = copy.getType();
	std::cout << "Assignment operator for Animal called." << std::endl;
	return (*this);
}

Animal::~Animal()
{
    std::cout << "Animal type " << this->getType() << " Destroyed " << std::endl << std::endl;
}

void Animal::makeSound() const
{
        std::cout << "some kind of noise " << this->_type << " Animal would do" << std::endl;
}

std::string const &Animal::getType() const
{
    return(this->_type);
}
