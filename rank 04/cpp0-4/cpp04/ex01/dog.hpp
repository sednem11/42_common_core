#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Dog: public Animal
{
    private:
        Brain *_brain;
    public:
        Dog(void);
        Dog(std::string const &type);
        Dog(Dog const &copy);
		Dog const	&operator=(Dog const &copy);
        ~Dog(void);
        Brain   &getBrain() const;
        void    setBrain(Brain const &brain);
        void    makeSound() const;
};


#endif