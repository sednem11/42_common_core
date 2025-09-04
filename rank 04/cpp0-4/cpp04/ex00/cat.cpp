#include "cat.hpp"

Cat::Cat(void): _type("Cat")
{
    std::cout << "Animal type " << this->getType() << " Created From: Animal " << std::endl << std::endl;
}

Cat::Cat(std::string const &type): Animal(type), _type("Cat")
{
    std::cout << "Animal type " << this->getType() << " Created From: Animal " << std::endl << std::endl;
}

Cat::Cat(Cat const &copy): Animal(copy)
{
	*this = copy;
	std::cout << "Cat from Animal " << Animal::_type << " copied." << std::endl;
}

Cat const	&Cat::operator=(Cat const &copy)
{
	std::cout << "Assignment operator for Dog from Animal " << Animal::_type << " called." << std::endl;
	Animal::operator=(copy);
	return (*this);
}

Cat::~Cat(void)
{
    std::cout << "Cat type: " << this->getType() << " Destroyed " << std::endl;
}

void Cat::makeSound() const
{
    std::cout << "hey im a cat of type: " << this->_type << " Meow?" << std::endl;
}