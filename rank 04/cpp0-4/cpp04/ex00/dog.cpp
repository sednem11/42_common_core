#include "dog.hpp"

Dog::Dog(void): _type("Dog")
{
    std::cout << "Animal type " << this->getType() << " Created From: Animal " << std::endl << std::endl;
}

Dog::Dog(std::string const &type): Animal(type), _type("Dog")
{
    std::cout << "Animal type " << this->getType() << " Created From: Animal " << std::endl << std::endl;
}

Dog::Dog(Dog const &copy): Animal(copy)
{
	*this = copy;
	std::cout << "Dog from Animal " << Animal::_type << " copied." << std::endl;
}

Dog const	&Dog::operator=(Dog const &copy)
{
	std::cout << "Assignment operator for Dog from Animal " << Animal::_type << " called." << std::endl;
	Animal::operator=(copy);
	return (*this);
}

Dog::~Dog(void)
{
    std::cout << "Dog type: " << this->getType() << " Destroyed " << std::endl;
}

void Dog::makeSound() const
{
    std::cout << "oi im a Dog of type: " << this->_type << " WOFF??" << std::endl;
}
