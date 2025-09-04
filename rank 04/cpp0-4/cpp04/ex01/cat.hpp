#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Cat: public Animal
{
    private:
        Brain *_brain;
    public:
    Cat(void);
    Cat(std::string const &type);
    Cat(Cat const &copy);
    Cat const	&operator=(Cat const &copy);
    ~Cat(void);
    Brain   &getBrain() const;
    void    setBrain(Brain const &brain);
    void    makeSound() const;
};


#endif