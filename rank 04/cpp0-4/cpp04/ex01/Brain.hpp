#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>

class Brain
{
private:
    std::string _ideas[100];
public:
    Brain();
    Brain(Brain const &copy);
    ~Brain();
    Brain const	&operator=(Brain const &copy);
    void    set_ideas(std::string const &idea, int const &index);
    std::string const &get_ideas(int const &index);
    
};


#endif