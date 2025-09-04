#include "cat.hpp"

Cat::Cat(void): Animal("Cat")
{
    std::cout << "Animal type " << this->getType() << " Created From: Animal " << std::endl;
    this->_brain = new Brain();
}

Cat::Cat(std::string const &type): Animal(type)
{
    std::cout << "Animal type " << this->getType() << " Created From: Animal " << std::endl;
    this->_brain = new Brain();
}

Cat::Cat(Cat const &copy)
{
    this->_brain = new Brain(*copy._brain);
	std::cout << "Cat copied." << std::endl;
}

Cat const	&Cat::operator=(Cat const &copy)
{
	Animal::operator=(copy);
	*this->_brain = *copy._brain;
	std::cout << "Assignment operator for Dog called." << std::endl;
	return (*this);
}

Cat::~Cat(void)
{
    delete this->_brain;
    std::cout << "Cat type: " << this->getType() << " Destroyed " << std::endl;
}

void Cat::makeSound() const
{
    std::cout << "hey im a cat of type: " << this->_type << " Meow?" << std::endl;
}


Brain &Cat::getBrain() const
{
    return(*this->_brain);
}

void    Cat::setBrain(Brain const &brain)
{
    *this->_brain = brain;
}

