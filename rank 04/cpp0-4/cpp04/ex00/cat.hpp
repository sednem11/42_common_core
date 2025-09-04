#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"

class Cat: public Animal
{
    private:
        std::string _type;
    public:
    Cat(void);
    Cat(std::string const &type);
    Cat(Cat const &copy);
    Cat const	&operator=(Cat const &copy);
    ~Cat(void);
    void    makeSound() const;
};


#endif