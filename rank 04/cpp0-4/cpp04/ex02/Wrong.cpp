#include "Wrong.hpp"

WrongAnimal::WrongAnimal(): _type("undefined")
{
    std::cout << "Animal type " << this->getType() << " Created" << std::endl << std::endl;
}

WrongAnimal::WrongAnimal(std::string const &type): _type(type)
{
    std::cout << "Animal type " << this->getType() << " Created" << std::endl << std::endl;
}

WrongAnimal::~WrongAnimal()
{
    std::cout << "Animal type " << this->getType() << " Destroyed " << std::endl << std::endl;
}

void WrongAnimal::makeSound() const
{
        std::cout << "some kind of noise a type: " << this->_type << " WrongAnimal would do" << std::endl;
}

std::string const &WrongAnimal::getType() const
{
    return(this->_type);
}

WrongCat::WrongCat(): _type("Undefined")
{
}

WrongCat::WrongCat(std::string const &type): WrongAnimal(type), _type(type)
{
}

WrongCat::~WrongCat()
{
    std::cout << "WrongCat type: " << this->getType() << " Destroyed " << std::endl << std::endl;
}

void WrongCat::makeSound() const
{
     std::cout << "(WrongAnimal noise!!!)" << std::endl;
}
