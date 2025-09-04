#ifndef WRONG_HPP
# define WRONG_HPP

#include <iostream>

class WrongAnimal
{
    protected:
        std::string _type;

    public:
        WrongAnimal();
        WrongAnimal(std::string const &type);
        virtual ~WrongAnimal();
        void    makeSound() const;
        std::string const   &getType() const;

};

class WrongCat: public WrongAnimal
{
    private:
        std::string _type;
    public:
        WrongCat();
        WrongCat(std::string const &type);
        ~WrongCat();
        void    makeSound() const;
};

#endif 