#include "dog.hpp"

Dog::Dog(void): Animal("Dog")
{
    std::cout << "Animal type " << this->getType() << " Created From: Animal " << std::endl;
    this->_brain = new Brain();
}

Dog::Dog(std::string const &type): Animal(type)
{
    std::cout << "Animal type " << this->getType() << " Created From: Animal " << std::endl;
    this->_brain = new Brain();
}

Dog::Dog(Dog const &copy)
{
    this->_type = copy._type;
    this->_brain = new Brain(*copy._brain);
	std::cout << "Dog copied." << std::endl;
}

Dog const	&Dog::operator=(Dog const &copy)
{
	Animal::operator=(copy);
	*this->_brain = *copy._brain;
	std::cout << "Assignment operator for Dog called." << std::endl;
	return (*this);
}

Dog::~Dog(void)
{
    delete this->_brain;
    std::cout << "Dog type: " << this->getType() << " Destroyed " << std::endl;
}

void Dog::makeSound() const
{
    std::cout << "oi im a Dog of type: " << this->_type << " WOFF??" << std::endl;
}

Brain &Dog::getBrain() const
{
    return(*this->_brain);
}

void    Dog::setBrain(Brain const &brain)
{
    *this->_brain = brain;
}
