#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <algorithm>

class Zombie{
    public:
        Zombie(void);
        Zombie(std::string name);
        ~Zombie(void);
        void announce(void);
        void setname(std::string name);
    private:
        std::string name;
};

Zombie  *newZombie(std::string name);

void    randomChump(std::string name);

# endif